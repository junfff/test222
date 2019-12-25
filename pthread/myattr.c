#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
void *func(void *arg)
{
	printf("this func runing\n");

	return (void *)100;
}
int main()
{
	pthread_t tid;
	pthread_attr_t attr;

	int ret = pthread_attr_init(&attr);
	if(ret != 0)
	{
		printf("pthread init error:%s\n",strerror(ret));
		exit(1);
	}

	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	ret = pthread_create(&tid,&attr,func,NULL);
	if(ret != 0)
	{
		printf("pthread create error:%s\n",strerror(ret));
		exit(1);
	}

	ret = pthread_join(tid,NULL);
	if(ret != 0)
	{
		printf("pthread join error:%s\n",strerror(ret));
		exit(1);
	}

  printf("join ret = %d\n",ret);

  pthread_exit((void *)1);
}
