#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *func1(void *arg)
{
  printf("this func1 runing!!\n");

	return (void *)111;
}
void *func2(void *arg)
{
  printf("this func2 runing!!\n");

	return (void *)222;
}
void *func3(void *arg)
{
	while(1)
	{
    //printf("this func3 runing!!\n");
		//sleep(1);
		
		pthread_testcancel();
	}

	return (void *)333;
}

int main()
{
	pthread_t tid;
	void *status = NULL;
  
	pthread_create(&tid,NULL,func1,NULL);
	pthread_join(tid,&status);
	printf("thread 1 exit code = %d\n",(int)status);

	pthread_create(&tid,NULL,func2,NULL);
	pthread_join(tid,&status);
	printf("thread 2 exit code = %d\n",(int)status);

	pthread_create(&tid,NULL,func3,NULL);
	sleep(3);
	int ret = pthread_cancel(tid);
	if(ret !=0)
	{
		perror("pthread cancel error !!!");
	}

	pthread_join(tid,&status);
	printf("thread 3 exit code = %d\n",(int)status);
   return 0;
}
