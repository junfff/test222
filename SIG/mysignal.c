#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

void myfunc(int signo)
{
   printf("hello signo is %d \n",signo);
}

int main()
{
    //alarm(5); 
     struct itimerval it, oldit;
     it.it_value.tv_sec = 5;
     it.it_value.tv_usec = 0;
     it.it_interval.tv_sec = 3;
     it.it_interval.tv_usec = 0;
  
     int ret = setitimer(ITIMER_REAL,&it,&oldit);
     if(ret == -1)
     {
       perror("setitimer error !!");                                          
       exit(1);
     }

   signal(SIGALRM,myfunc);
    

   //sigemptyset(&set)  //把集合清 0

   //sigfillset(&set)  //全部设置 为 1               

   //sigaddset(sigset_t *set,int signum)  //将某个信号加入信号集 将某个信号 设置 1

   //sigdelset(sigset_t *set,int signum)  //删除某个信号   将某个信号 设置 0

   //sigismember(const sigset_t *set,int signum) //判断某个信号是否在 信号集   1 存在  0 不存在 -1 出错

	 // how :SIG_BLOCK SIG_UNBLOCK SIG_SETMASK     set 新值   oldset 旧 的值
	 //sigprocmask(int how,const sigset_t *set,sigset_t oldset );

   
   //sigpending(sigset_t *set)  //通过传出参数  读出 当前的 未决信号集







   while(1)
   {
   	 printf("i am sleep ing...\n");
   	 sleep(1);
   }
   




   return 0;
}
