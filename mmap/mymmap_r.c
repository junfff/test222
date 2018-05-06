#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>

struct STU
{
   int id;
   char name[20];
   char sex;

};

void sys_err(char *str)
{
   perror(str);
   exit(1);
}
int main(int argc,char *argv[])
{
   printf("start !!\n");
   
   int fd;
   struct STU student;
   struct STU *mm;
   
   if(argc < 2)
   {
      printf("a.out file_shared !! \n");
      exit(-1);
   }
   
   fd = open(argv[1],O_RDONLY);
   if(fd == -1)
   {
      sys_err("open error !!!\n");
   }

   mm = mmap(NULL,sizeof(student),PROT_READ,MAP_SHARED,fd,0);
   if(mm == MAP_FAILED)
   {
      sys_err("mmap error !!\n");

   }
   
   close(fd);

   while(1)
   {
     printf("id = %d \t name = %s \t %c \n",mm->id,mm->name,mm->sex);
     sleep(2);
   }

   munmap(mm,sizeof(student));







   return 0;
}