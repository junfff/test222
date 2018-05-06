#include <sys/stat.h>
#include <sys/wait.h>
  #include <sys/types.h>
         #include <unistd.h>
     #include <string.h>
       #include <stdio.h>
         #include <math.h>
           #include <stdlib.h>
             #include <float.h>
               #include <limits.h>
                 #include <ctype.h>
                  #include "cJSON.h"
                   #include <fcntl.h>
                    #include "mychat.h"
                    #include "chat_my_server.h"

void show(char *str)
{
	 pid_t pid = fork();
	 if(pid == -1)
	 {
	 	 perror("fork error !!");
	 }
	 else if(pid == 0)
	 {
     printf("info:%s\n",str);
	 }
	 else
	 {
      wait(NULL);
	 }
}

int main()
{
    printf("start myserver !!!\n");
   //1 打开公共FIFO 阻塞等待读取
   Init(SERVER_FIFO);
   //2 读到内容字符串解析

   while(1)
   {
   	 show("waitint client msg...\n");
     c_msg *cmsg = ReadFifo();
    
    printf("num = %d  >>>>>>",cmsg->num);
    if(cmsg->num == 1)
    {
    	 printf("用户注册:%s",cmsg->src.name);
    }
   else if(cmsg->num == 2)
   {
      printf("用户聊天:%s to %s !!",cmsg->src.name,cmsg->dest.name);
   }
   else if(cmsg->num == 3)
   {
   	 printf("用户退出：%s",cmsg->src.name);
   }
   //3 判断协议号num
   //  1 用户注册
   //    非阻塞写打开新用户创建的私有FIFO
   //    增加在线列表节点
   //  2 用户聊天
   //    取出dst
   //    中转数据给客户端
   //  3 用户退出 
   //    将用户从在线列表中移除
   //返回第一步1，继续阻塞在公共FIFO读等待

   sleep(1);
 	 }   
   printf("finish myserver !!!\n");
   return 0;
}
