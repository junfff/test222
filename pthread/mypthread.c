#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *OnPthread(void *str)
{
	pthread_t tid = pthread_self();
	printf("this is on pthread !!!str is:%s  pthread id :%lu  pid = %d\n",(char*)str,tid,getpid());



   return NULL;
}

int main()
{
   int ret = 0;
	 pthread_t tid;

	 printf("int main 1:pthread id = %lu  pid = %d\n",pthread_self(),getpid());
	 ret = pthread_create(&tid,NULL,OnPthread,"Hello pthread!!");
   if(ret < 0)
	 {
	    perror("pthread create error !!!");
			exit(1);
	 }
   
	 printf("create sueecc !!tid is:%lu\n",tid);
	 printf("int main 2:pthread id = %lu  pid = %d\n",pthread_self(),getpid());
   while(1)
	 {
	    printf("this is parent waiting \n");
			sleep(1);
	 }
   return 0;
}
