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

int main()
{
	int num = 10;
   int ret = 0;
	 pthread_t tid[num];

	 printf("int main 1:pthread id = %lu  pid = %d\n",pthread_self(),getpid());

	 int i = 0;
	  for(i=0;i<num;i++)
	 {
		 ret = pthread_create(&tid[i],NULL,OnPthread,(void *)i);
     if(ret < 0)
 		 {
	    perror("pthread create error !!!");
			exit(1);
 		 }

	 }
   
	 //printf("create sueecc !!tid is:%lu\n",tid);
	 //printf("int main 2:pthread id = %lu  pid = %d\n",pthread_self(),getpid());
   
			
 
			for(i=0;i<num;i++)
			{
			exit_t *retval;
			pthread_join(tid[i],(void **)&retval);  
			printf("on join tid + %lu retval var =  %d str = %s\n",tid[i],retval->var,retval->str);

			free(retval);
			}
	    printf("this is parent finish var = %d ret = %d\n",var,ret);
  pthread_exit((void *)1);
}
