#include <sys/wait.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void OnError(char *str)
{
   perror(str);
   exit(1);
}
void testLog(int str)
{
   printf("testLog:%d ! \n",str);
   exit(1);
}
int GetFileLen(int fd)
{
   struct stat buf;
   int ret = fstat(fd,&buf);
   if(ret == 0)
   {
      return (int)buf.st_size;
   }
  return -1;
}
void SleepPrintf(char *str)
{
   printf("程序进度：%s\n",str);
  // sleep(2);
}

char *read_fd;
 char *write_fd;
int num = 10;
char *str[1024];
float rate = 10;
float doneNum;
int cpNum;
 int lastNum;
void *OnCopy(void *arg)
{
	int index =(int)arg;

      SleepPrintf("子进程开始拷贝工作 ！");
      //子进程开始拷贝工作
      //sleep(3);
      int last = num -1;
      if(index < last)
      {
         memcpy(write_fd + (cpNum * index),read_fd + (cpNum * index ),cpNum);
      }
      else if(index == last)
      {
         memcpy(write_fd + (cpNum * index),read_fd + (cpNum * index ),lastNum);
      }

      printf("child copy finish ! index = %d \n",index);
}










int main()
{
	SleepPrintf("程序开始！指定创建进程个数 ！！！");
	int ret = 0;
   //指定创建子进程的个数
   num = 10;
   SleepPrintf("打开源文件 ！！");
   //打开源文件
   int fd = open("all.txt",O_RDONLY);
   if(fd == -1)
   {
      OnError("open all.txt error !!");
   }
   SleepPrintf("打开目的文件 ！！！");
   //打开目的文件
   int tofd = open("target.txt",O_RDWR | O_CREAT,0644);
   //unlink("target.txt");
   if(tofd == -1)
   {
     OnError("open tofd error !!");
   }
   SleepPrintf("获取文件大小 ！！");
   //获取文件大小
   int total = GetFileLen(fd);
   //total = lseek(fd,0,SEEK_END);
   if(total == -1)
   {
     OnError("lseek error !!");
   }
   SleepPrintf("根据文件大小扩展目标文件！");
   //根据文件大小扩展目标文件
   ftruncate(tofd,total);
   SleepPrintf("为源文件创建映射区！");
   //为源文件创建映射
   read_fd = mmap(NULL,total,PROT_READ,MAP_SHARED,fd,0);
   if(read_fd == MAP_FAILED)
   {
     OnError("read_fd error !!!");
   }
   SleepPrintf("为目标文件创建映射区！");
   //为目标文件创建映射区
   write_fd = mmap(NULL,total,PROT_WRITE,MAP_SHARED,tofd,0);
   if(write_fd == MAP_FAILED)
   {
      OnError("write_fd error !!");
   }
   SleepPrintf("求出每个子进程该拷贝的字节 ！");
   //求出每个子进程该拷贝的字节
    cpNum = total/num;
   lastNum =cpNum + total%num;
   SleepPrintf("创建N个子进程 ！");
   //创建N个子进程
   int i = 0;
   pthread_t pid[num];
   while(i < num)
   {
     ret = pthread_create(&pid[i],NULL,OnCopy,(void *)i);
     if(ret != 0)
     {
       OnError("fork error !!");
     }
     i++;
   }
   
      printf("主进程开始等待，释放子进程！\n");
      //释放子进程
      int wNum = 0;
      printf("main start waitint... !!!\n");
      while(wNum < num)
      {
        int wpid = pthread_join(pid[wNum],NULL);
	
				if(wpid == 0)
				{
           printf("main wait pid = %lu !! \n",pid[wNum]);
 					 wNum++;
				}
				printf("main waiting... wNum = %d \n",wNum);
      	//sleep(1);
      }
      SleepPrintf("释放映射区！！");
      //释放映射区
      ret =  munmap(read_fd,total);
      if(ret == -1)
      {
        OnError("munmap read_fd error !!");
      }
      ret = munmap(write_fd,total);
      if(ret == -1)
      {
        OnError("munmap write_fd error !!!");
      }
      printf("Main Finish !!!wNum = %d \n",wNum);
   

    //  printf("test log total = %d cpNum = %d lastNum = %d !!\n",total,cpNum,lastNum);
    //   testLog(total);

     return 0;
}
