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
   struct STU student = {10,"anynii",'m'};
   struct STU *mm;
   
   if(argc < 2)
   {
      printf("a.out file_shared !! \n");
      exit(-1);
   }
   
   fd = open(argv[1],O_RDWR | O_CREAT,0644);
   if(fd == -1)
   {
      sys_err("open error !!!\n");
   }
   
   ftruncate(fd,sizeof(student));

   mm = mmap(NULL,sizeof(student),PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
   if(mm == MAP_FAILED)
   {
      sys_err("mmap error !!\n");

   }
   
   close(fd);
   
   while(1)
   {
      memcpy(mm,&student,sizeof(student));
      student.id++;
      sleep(1);

   }
   
   munmap(mm,sizeof(student));







   return 0;
}
