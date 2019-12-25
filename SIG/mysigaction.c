#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

//         struct sigaction {
//               void     (*sa_handler)(int);
//               void     (*sa_sigaction)(int, siginfo_t *, void *);
 //              sigset_t   sa_mask;
 //              int        sa_flags;
 //              void     (*sa_restorer)(void);
  //         };
void myfunc(int num)
{
   printf("on myfunc num:%d\n",num);
   sleep(10);
   printf("------finish--------\n");
}
int main()
{
	 struct sigaction act;
	 act.sa_handler = myfunc;
   sigemptyset(&act.sa_mask);
   sigaddset(&act.sa_mask,SIGQUIT);
   act.sa_flags = 0; //默认属性 信号捕捉函数执行期间 自动屏蔽本信号

    

   int ret = sigaction(SIGINT,&act,NULL);
   if(ret < 0)
   {
      perror("sigaction error !!");
      exit(1);
   }


   while(1);



   return 0;
}
