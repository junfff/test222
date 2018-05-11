#include <sys/mman.h>
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
#include "info_list.h"

void show(char *str)
{
	// pid_t pid = fork();
	// if(pid == -1)
	// {
	 	// perror("fork error !!");
	// }
	 //else if(pid == 0)
	// {
     printf("info:%s\n",str);
//	 }
	// else
	// {
   //   wait(NULL);
	// }
}
void OnMsg(SMP *server_mmap)
{
	 int showHint = 1;
   while(1)
   {
     //printf("消息线程 命令是：%s  status=%d \n",server_mmap->cmd,server_mmap->status);
   	 if(server_mmap->status == SMP_STOP)
   	 {
   	    sleep(1);
   	    return;
   	 }
     if(showHint == 1)
     {
   	    show("waitint client msg...\n");
        showHint = 0;
     }
     c_msg *cmsg = ReadFifo();
    
     if(NULL == cmsg)
     {
     	  sleep(1);
        continue;
     }
    showHint = 1;
    printf("num = %d  >>>>>>",cmsg->num);
    if(cmsg->num == 1)
    {
    	 printf("用户注册:%s\n",cmsg->src.name);
    	 int ret = Add_List(&cmsg->src);
    	 if(ret == -1)
    	 {
    	 	 printf("添加List 失败 ！！\n");
    	 }
    	 else
    	 {
    	 	 printf("成功添加 用户:%s\n",cmsg->src.name);
    	 	 SendClientMsg();
    	 }
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


}
void OnInput(SMP *server_mmap)
{
 while(1)
 {
   printf("输入 quit 停止服务器！！\n");
   scanf("%s",server_mmap->cmd);
   if(strcmp(server_mmap->cmd,"quit") == 0)
   {
   	    sleep(1);
   	    //printf("输入线程 收到 停止命令 ！");
   	    return;
   }
 }
}
int main()
{
    printf("start myserver !!!\n");
   //1 打开公共FIFO 阻塞等待读取
   Init(SERVER_FIFO);
   Init_List();

   //2 读到内容字符串解析
    
   //smp
   SMP *server_mmap;   
   int fd = open("tmp_mmap",O_RDWR | O_CREAT,0644);
   if(fd == -1)
   {
   	 perror("open error !!");
   	 exit(1);
   }
   ftruncate(fd,sizeof(SMP));
   server_mmap = mmap(NULL,sizeof(SMP),PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
   if(server_mmap == MAP_FAILED)
   {
   	 perror("mmap error !!");
   	 exit(1);
   }
   unlink("tmp_mmap");
   close(fd);

	 server_mmap->status = SMP_START; //服务器运行状态

   pid_t msg_pid;
   pid_t input_pid;

   msg_pid = fork();
   if(msg_pid == -1)
   {
      perror("fork msg pid error !!");
      exit(1);
   }
   else if(msg_pid == 0)
   {
      OnMsg(server_mmap);
      return 0;
   }


   input_pid = fork();
   if(input_pid == -1)
   {
      perror("fork input pid error !!");
      exit(1);
   }
   else if(input_pid == 0)
   {
      OnInput(server_mmap);
      return 0;
   }


   while(1)
   {
      if(strcmp(server_mmap->cmd,"quit") == 0)
      {
         server_mmap->status = SMP_STOP;
         break;
      }
      //printf("主线程 命令是：%s \n",server_mmap->cmd);
      sleep(1);
   }



   //printf("主线城 开始回收 子线程！！！");
   waitpid(msg_pid,NULL,0);//WNOHANG 非阻塞 0 阻塞
   waitpid(input_pid,NULL,0);


   munmap(server_mmap,sizeof(SMP));
   Deinit_List();
   remove(SERVER_FIFO);
   //unlink(SERVER_FIFO);
   printf("finish myserver !!!\n");
   return 0;
}
