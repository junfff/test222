#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
   pid_t pid;
   pid = fork();
   if(pid == 0)
   {
      printf("---child, my parent = %d ,going to sleep 10s \n",getppid());
      char *bug="sadfsdffdsadf";
      //bug[0] ='h';
      //int a =5/0;
      sleep(20);
      printf("----------child die ---------------  \n");
      //exit(88);
   }
   else if(pid > 0)
   {
	   int wstatus;

	   //pid_t wpid = wait(&wstatus);
	   pid_t wpid;
	   do
	   {
	     wpid  = waitpid(pid,&wstatus,WNOHANG);
	     sleep(1);
	   }
	   while(wpid == 0);
	  if( WIFEXITED(wstatus))
	  {
              printf("child exit with %d \n",  WEXITSTATUS(wstatus));

	  }
	  if(WIFSIGNALED(wstatus))
	  {
		  printf("child signaled exit with  %d \n",WTERMSIG(wstatus));
	  }
	   printf("---------wpid is %d!!wstatus is %d  \n",wpid,wstatus);

	   while(1)
	   {
      printf("i am parent, pid = %d , myson = %d  \n",getpid(),pid);
      sleep(1);
	   }
   }
   else
   {
      perror("fork error !!! \n");
      return 1;
   }

   //int ret =  wait();


	return 0;
}
