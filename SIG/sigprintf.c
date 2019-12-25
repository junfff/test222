#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/signal.h>
#include <sys/time.h>
int main()
{
	alarm(5);
  sigset_t myset,penset,oldset;

	sigemptyset(&myset);
	sigaddset(&myset,SIGQUIT);
	sigaddset(&myset,SIGALRM);
	int ret = sigprocmask(SIG_BLOCK,&myset,&oldset);
	if(ret == -1)
	{
		perror("sigprocmask error !!");
		exit(1);
	}
   
  while(1)
  {
  ret = sigpending(&penset);
  if(ret == -1)
  {
     perror("sigpending error !! ");
     exit(1);
  }
  for(int i =1;i<33;i++)
  {
     ret = sigismember(&penset,i);
     //printf("第 %d 信号 ret: %d\n",i,ret);
     printf("%d",ret);
  }
  printf("\n");
  sleep(1);
  }

 
 	return 0;
}
