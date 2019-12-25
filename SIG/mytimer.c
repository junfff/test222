#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main()
{
	 struct itimerval it, oldit;
	 it.it_value.tv_sec = 1;
	 it.it_value.tv_usec = 0;
	 it.it_interval.tv_sec = 2;
	 it.it_interval.tv_usec = 0;

   int ret = setitimer(ITIMER_REAL,&it,&oldit); 
   if(ret == -1)
   {
   	 perror("setitimer error !!");
   	 exit(1);
   }
    
   int i = 0 ;
   while(1)
   {
   	 i++;
   	 printf("setitimer i = %d\n",i);
   }



   return 0;
}
