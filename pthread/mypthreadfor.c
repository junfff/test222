#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


int var = 0;

void *OnPthread(void *str)
{
	int i = (int)str;
	var +=i;
	pthread_t tid = pthread_self();
	//sleep(i);
	printf("this is on pthread !!!str is:%d  pthread id :%lu  pid = %d\n",i,tid,getpid());



	pthread_exit(0);
  // return NULL;
}

int main()
{
	int num = 10;
   int ret = 0;
	 pthread_t tid;

	 printf("int main 1:pthread id = %lu  pid = %d\n",pthread_self(),getpid());

	 for(int i=0;i<num;i++)
	 {
		 //char str[80];
		//sprintf(str, "%s%d xx", "Hello pthread!!", i);  
	 ret = pthread_create(&tid,NULL,OnPthread,(void *)i);
   if(ret < 0)
	 {
	    perror("pthread create error !!!");
			exit(1);
	 }

	 }
   
	 printf("create sueecc !!tid is:%lu\n",tid);
	 printf("int main 2:pthread id = %lu  pid = %d\n",pthread_self(),getpid());
		//	sleep(num);
	    printf("this is parent waiting var = %d\n",var);
  // return 0;
  pthread_exit((void *)1);
}
