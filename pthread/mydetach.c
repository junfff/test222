#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

typedef struct
{
  int var;
	char str[64];
}exit_t;
int var = 0;

void *OnPthread(void *str)
{
	int i = (int)str;
	var +=i;
	pthread_t tid = pthread_self();
	//sleep(i);
	printf("this is on pthread !!!str is:%d  pthread id :%lu  pid = %d\n",i,tid,getpid());


	exit_t *info =(exit_t *)malloc(sizeof(exit_t));
	info->var = i;
	strcpy(info->str,"pthread_exit");
	pthread_exit((void *)info);
}

void CheckRet(int ret,char *str)
{
   if(ret != 0)
	 {
	  //  perror(str);
		  printf(">>>>>>> ret =%d error info:%s\n",ret,strerror(ret));
			exit(1);
	 }
}
int main()
{
   int ret = 0;
	 pthread_t tid;

	 printf("int main 1:pthread id = %lu  pid = %d\n",pthread_self(),getpid());
	 ret = pthread_create(&tid,NULL,OnPthread,(void *)110);
	 CheckRet(ret,"pthread create error !!");

	 //pthread_detach(tid); //分离线程 自动退出 无需回收
	 //ret = -1;
   CheckRet(ret,"pthread detach error!!");

	  exit_t *info;
	 ret = pthread_join(tid,(void **)&info);
   CheckRet(ret,"pthread join error !!!");





   pthread_exit(0);
}
