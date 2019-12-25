/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：threadpool.c
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年06月24日 17:52(Sunday) 
 *   描    述：
 *
 ================================================================*/

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include "../include/threadpool.h"
#include "../include/myevents.h"
#include <event.h>


int threadpool_add_threadnum(threadpool_t *pool)
{
	int all_threadnum = -1;
	pthread_mutex_lock(&(pool->lock));
	all_threadnum = pool->live_thr_num;
	pthread_mutex_unlock(&(pool->lock));
	return all_threadnum;
}
int threadpool_busy_threadnum(threadpool_t *pool)
{
	int busy_threadnum = -1;
	pthread_mutex_lock(&(pool->lock));
	busy_threadnum = pool->busy_thr_num;
	pthread_mutex_unlock(&(pool->lock));
	return busy_threadnum;
}
int is_thread_alive(pthread_t tid)
{
	int kill_rc = pthread_kill(tid,0); // 发送 信号 0 测试 线程 是否 存活
	if(kill_rc == ESRCH)
	{
		return false;
	}
	return true;
}


int threadpool_add(threadpool_t *pool,void *(*function)(void *arg),void *arg)
{
	pthread_mutex_lock(&(pool->lock));

	while((pool->queue_size == pool->queue_max_size) && (!pool->shutdown)) //达到上限  阻塞等待 
	{
		pthread_cond_wait(&(pool->queue_not_full),&(pool->lock));
	}

	if(pool->shutdown)
	{
		pthread_mutex_unlock(&(pool->lock));
	}

	if(NULL != pool->task_queue[pool->queue_rear].arg)
	{
		free(pool->task_queue[pool->queue_rear].arg);
		pool->task_queue[pool->queue_rear].arg = NULL;
	}


	pool->task_queue[pool->queue_rear].function = function;   // 任务入队
	pool->task_queue[pool->queue_rear].arg = arg;
	pool->queue_rear = (pool->queue_rear + 1) % pool->queue_max_size;
	pool->queue_size++;


	pthread_cond_signal(&(pool->queue_not_empty));  //唤醒一个 等待任务的线程
	pthread_mutex_unlock(&(pool->lock));


	return 0;
}
void *threadpool_thread(void *arg)
{
	threadpool_t *pool = (threadpool_t *)arg;
	threadpool_task_t task;

	while(true)
	{
		pthread_mutex_lock(&(pool->lock));

		while((pool->queue_size == 0) && (!pool->shutdown))  // 无任务时 阻塞 条件变量， 有任务时 跳过 while  
		{
			printf("===========\n");
			printf("thread 0x%x is waiting...\n",(unsigned int)pthread_self());
			printf("============================\n");
			pthread_cond_wait(&(pool->queue_not_empty), &(pool->lock));

			if(pool->wait_exit_thr_num > 0)
			{
				pool->wait_exit_thr_num--;

				if(pool->live_thr_num > pool->min_thr_num)
				{
					printf("thread 0x%x is exiting\n",(unsigned int)pthread_self());
					pool->live_thr_num--;
					pthread_mutex_unlock(&(pool->lock));
					pthread_exit(NULL);
				}
			}
		}
		if(pool->shutdown)
		{
			printf("thread 0x%x is exiting\n",(unsigned int)pthread_self());
			pthread_mutex_unlock(&(pool->lock));
			pthread_exit(NULL);
		}


		task.function = pool->task_queue[pool->queue_front].function;
		task.arg = pool->task_queue[pool->queue_front].arg;

		pool->queue_front = (pool->queue_front+1) % pool->queue_max_size;
		pool->queue_size--;


		pthread_cond_broadcast(&(pool->queue_not_full));

		pthread_mutex_unlock(&(pool->lock));


		printf("============================\n");
		printf("thread 0x%x working starting...\n",(unsigned int)pthread_self());
		printf("===========\n");
		pthread_mutex_lock(&(pool->thread_counter));
		pool->busy_thr_num++;
		pthread_mutex_unlock(&(pool->thread_counter));

		task.function(task.arg);



		printf("thread 0x%x working end...\n",(unsigned int)pthread_self());
		pthread_mutex_lock(&(pool->thread_counter));
		pool->busy_thr_num--;
		pthread_mutex_unlock(&(pool->thread_counter));
	}

	pthread_exit(NULL);

}

void *adjust_thread(void *arg)
{
	int i;
	threadpool_t *pool = (threadpool_t *)arg;

	while(!pool->shutdown)
	{
		sleep(DEFAULT_TIME);

		pthread_mutex_lock(&(pool->lock));

		int queue_size = pool->queue_size;
		int live_thr_num = pool->live_thr_num;
		pthread_mutex_unlock(&(pool->lock));


		pthread_mutex_lock(&(pool->thread_counter));
		int busy_thr_num = pool->busy_thr_num;
		pthread_mutex_unlock(&(pool->thread_counter));

		// 是否 需要 添加 线程 的算法  任务数 大于 最小 线程池 个数   且  存活 的 线程 数  少于 最大 线程 数   
		// 任务太多  线程 太少  忙不过来
		if(queue_size >= MIN_WAIT_TASK_NUM && live_thr_num < pool->max_thr_num)
		{
			pthread_mutex_lock(&(pool->lock));

			int add = 0;

			for(i=0;i<pool->max_thr_num && add < DEFAULT_THREAD_VARY && pool->live_thr_num < pool->max_thr_num;i++)
			{
				if(pool->threads[i] == 0 || !is_thread_alive(pool->threads[i]))
				{
					pthread_create(&(pool->threads[i]),NULL,threadpool_thread,(void *)pool);
					add++;
					pool->live_thr_num++;
				}
			}

			pthread_mutex_unlock(&(pool->lock));
		}


		// 任务太少  员工太多  裁员
		if((busy_thr_num*2) < live_thr_num && live_thr_num > pool->min_thr_num)
		{
			pthread_mutex_lock(&(pool->lock));
			pool->wait_exit_thr_num = DEFAULT_THREAD_VARY;
			pthread_mutex_unlock(&(pool->lock));

			for(i=0;i<DEFAULT_THREAD_VARY;i++)
			{
				pthread_cond_signal(&(pool->queue_not_empty));   // 让空闲的线程 自行 终止
			}
		}
	}
	return NULL;
}
int threadpool_free(threadpool_t *pool)
{
	if(NULL == pool)
	{
		return -1;
	}

	if(pool->task_queue)
	{
		free(pool->task_queue);
	}

	if(pool->threads)
	{
		free(pool->threads);

		pthread_mutex_lock(&(pool->lock));
		pthread_mutex_destroy(&(pool->lock));

		pthread_mutex_lock(&(pool->thread_counter));
		pthread_mutex_destroy(&(pool->thread_counter));

		pthread_cond_destroy(&(pool->queue_not_empty));
		pthread_cond_destroy(&(pool->queue_not_full));
	}

	free(pool);
	pool = NULL;

	return 0;
}
int threadpool_destroy(threadpool_t *pool)
{
	int i;
	if(pool == NULL)
	{
		return -1;
	}

	pool->shutdown = true;

	pthread_join(pool->adjust_tid,NULL);

	for(i=0;i<pool->live_thr_num;i++)
	{
		pthread_cond_broadcast(&(pool->queue_not_empty));
	}

	for(i=0;i<pool->live_thr_num;i++)
	{
		pthread_join(pool->threads[i],NULL);
	}

	threadpool_free(pool);

	return 0;
}
threadpool_t *threadpool_create(int min_thr_num,int max_thr_num,int queue_max_size)
{
	int i;
	threadpool_t *pool = NULL;
	do
	{
		pool = (threadpool_t *)malloc(sizeof(threadpool_t));
		if(pool == NULL)
		{
			printf("malloc threadpool fail\n");
			break;
		}

		pool->min_thr_num = min_thr_num;
		pool->max_thr_num = max_thr_num;
		pool->busy_thr_num = 0;
		pool->live_thr_num = min_thr_num;
		pool->queue_size = 0;
		pool->queue_max_size = queue_max_size;
		pool->queue_front = 0;
		pool->queue_rear = 0;
		pool->shutdown = false;


		pool->threads = (pthread_t *)malloc(sizeof(pthread_t)*max_thr_num);
		if(pool->threads == NULL)
		{
			printf("malloc threads fail\n");
			break;
		}

		memset(pool->threads,0,sizeof(pthread_t)*max_thr_num);

		pool->task_queue = (threadpool_task_t *)malloc(sizeof(threadpool_task_t)*queue_max_size);
		if(NULL == pool->task_queue)
		{
			printf("malloc task_queue fail\n");
			break;
		}
		memset(pool->task_queue,0,sizeof(threadpool_task_t)*queue_max_size);


		if(pthread_mutex_init(&(pool->lock),NULL) != 0
					|| pthread_mutex_init(&(pool->thread_counter),NULL) != 0
					|| pthread_cond_init(&(pool->queue_not_full),NULL) != 0
					|| pthread_cond_init(&(pool->queue_not_empty),NULL) != 0)
		{
			printf("init the lock or cond fail\n");
			break;
		}


		for(i=0;i<min_thr_num;i++)
		{
			pthread_create(&(pool->threads[i]),NULL,threadpool_thread,(void *)pool);
			printf("start thread 0X%x...\n",(unsigned int)pool->threads[i]);
		}
		pthread_create(&(pool->adjust_tid),NULL,adjust_thread,(void *)pool);

		return pool;
	}
	while(false);

	threadpool_free(pool);
	return NULL;
}

void *process_event(void *arg)
{
	struct myevent_s *ev = (struct myevent_s *)arg;
	//printf("process event fd:%d,events:%d , callback:%p,arg:%p\n",ev->fd,ev->events,ev->call_back,ev->arg);
	ev->call_back(ev->arg);

	return NULL;
}
void *process(void *arg)
{
	int *i = (int *)arg;
	printf("thread 0x%x working on task %d\n",(unsigned int)pthread_self(),*i);
	sleep(1);
	printf("task %d is end\n",*i);

	return NULL;
}

int Start()
{
	threadpool_t *thp = threadpool_create(3,100,100); // 创建 线程  最小线程，最大，队列最大
	printf("pool inited\n");

	int num[20],i;
	for(i=0;i<20;i++)
	{
		num[i]=i;
		printf("add task %d\n",i);
		threadpool_add(thp,process,(void *)&num[i]);
	}
	sleep(10);
	threadpool_destroy(thp);
	return 0;
}
