  #include <unistd.h>
       #include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
       #include <signal.h>


int main()
{
    pid_t kpid;
    int num = 5;
    for(int i =0;i<num;i++)
    {
     pid_t pid =  fork();
     if(pid == -1)
     {
        perror("fork error !!");
        exit(1);
     }
     else if(pid == 0)
     {
        sleep(1000000); 
        break;
     }
     else
    {
       if(i == 2)
        {
           kpid = pid;
           printf("kpid == %d\n",kpid);
         }
    }

    }






	pid_t pid = getpid();
	printf("this pid = %d\n",pid);
   int ret = kill(kpid,SIGKILL);
  if(ret == -1)
  {
     perror("kill error !!");
     exit(1);
  }
   return 0;
}
