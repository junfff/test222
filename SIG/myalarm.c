#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
   alarm(1);
   int i =0;
	 while(1)
	 {
     i++;
     printf("myalarm i == %d \n",i);
	 }
   return 0;
}
