/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：threadpool.h
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年06月24日 18:22(Sunday) 
 *   描    述：
 *
 ================================================================*/


#pragma once
//#ifndef _THREADPOOL_H_
//#define _THREADPOOL_H_
#include <pthread.h>

#define DEFAULT_TIME 10
#define MIN_WAIT_TASK_NUM 10
#define DEFAULT_THREAD_VARY 10
#define true 1
#define false 0
typedef struct
{
	void *(*function)(void *);
	void *arg;
}threadpool_task_t;

struct threadpool_t
{
	pthread_mutex_t lock;
	pthread_mutex_t thread_counter;
	pthread_cond_t queue_not_full;
	pthread_cond_t queue_not_empty;

	pthread_t *threads;
	pthread_t adjust_tid;
	threadpool_task_t *task_queue;

	int min_thr_num;
	int max_thr_num;
	int live_thr_num;
	int busy_thr_num;
	int wait_exit_thr_num;

	int queue_front;
	int queue_rear;
	int queue_size;
	int queue_max_size;

	int shutdown;
};


//extern threadpool_t *thp;

int threadpool_add_threadnum(threadpool_t *pool);
int threadpool_busy_threadnum(threadpool_t *pool);
int is_thread_alive(pthread_t tid);
int threadpool_add(threadpool_t *pool,void *(*function)(void *arg),void *arg);
int threadpool_destroy(threadpool_t *pool);
threadpool_t *threadpool_create(int min_thr_num,int max_thr_num,int queue_max_size);
void *process_event(void *arg);
int Start();




//#endif



