#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

int var = 0;

void *OnPthread(void *str)
{
	while(1)
	{
		sleep(1);
	}
}

int main()
{
	int num = 0;
   int ret = 0;
	 pthread_t tid;

	 while(1)
	 {
	 ret = pthread_create(&tid,NULL,OnPthread,NULL);
   if(ret != 0)
	 {
	    printf("pthread create error = %s\n !!!",strerror(ret));
			exit(1);
	 }
num++;
	 printf("num = %d\n",num);
	 }
   
  pthread_exit((void *)1);
}
