#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
   int num = 0;	
   pid_t pid;	
   printf("this is  fork test !!!\n ");

   for(int i=0;i<5;i++)
   {
   pid = fork();
   
  // printf("======\n");
   if(pid == -1)
   {
      perror("fork error !!! \n");
      exit(1);
   }
   else if(pid == 0)
   {
      sleep(i);	   
      printf("这个是第 %d 个子进程！child pid= %d,ppid= %d\n",i+1,getpid(),getppid());
      break;
   }
   else
   {
	 //  printf("this is parent pid = %d  ppid = %d\n",getpid(),getppid());
   }
   }
   if(pid!=0)
   {
   //sleep(5);
   printf("finish !!!!pid=%d\n",getpid());
   }
   return 0;
}
