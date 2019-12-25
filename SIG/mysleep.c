#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

 //      struct sigaction {
   //            void     (*sa_handler)(int);
     //          void     (*sa_sigaction)(int, siginfo_t *, void *);
       //        sigset_t   sa_mask;
         //      int        sa_flags;
           //    void     (*sa_restorer)(void);
          // };

void myfunc()
{
  printf("on myfunc \n");
}
void mysleep(int sec)
{
	 struct sigaction act,oldact;
	 act.sa_handler = myfunc;
	 sigemptyset(&act.sa_mask);
   sigaction(SIGALRM,&act,&oldact);
   alarm(sec);

	 pause();

}

int main()
{
	while(1)
	{
	  mysleep(3);
		printf("on mysleep finish !!\n");  
	}

   return 0;  
}
