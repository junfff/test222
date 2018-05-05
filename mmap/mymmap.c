#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
  #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
#include <stdlib.h>

int var = 100;
int main()
{
   printf("start !! ");

   int *p;
   pid_t pid;
   int len = 4;
   int fd;
   //fd = open("temp",O_RDWR | O_CREAT | O_TRUNC,0644);
   fd = open("/dev/zero",O_RDWR);
   if(fd < 0)
   {
	perror("open error !!\n");
	exit(1);
   }
   //unlink("temp");
   //ftruncate(fd,len);

   // MAP_ANONYMOUS
   //p = (int *)mmap(NULL,len,PROT_READ | PROT_WRITE,MAP_SHARED | MAP_ANONYMOUS,-1,0);
   p = (int *)mmap(NULL,len,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
   //p = (int *)mmap(NULL,len,PROT_READ | PROT_WRITE,MAP_PRIVATE,fd,0);
   if(p == MAP_FAILED)
   {
	perror("mmap error !!\n");
	exit(1);
   }
   close(fd);


   pid = fork();
   if(pid == -1)
   {
	perror("fork error !!");
	exit(1);
   }
   if(pid == 0)
   {
	*p = 2000;
	var = 1000;
	printf("child, *p = %d, var = %d \n",*p,var);
   }
   else
   {
     sleep(2);
     printf("parent , *p = %d ,var = %d \n",*p,var);

     int ret = munmap(p,len);
     if(ret == -1)
     {
	perror("munmap error !!\n");
	exit(1);
     }

     wait(NULL);
   }
   return 0;
}
