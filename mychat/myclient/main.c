#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "chat_fifo.h"
#include "mychat.h"
#include "s2j.h"

int fd = 0;
char *fifo_path[128];
s_msg myinfo;

void OnRegister(my_usr info)
{
   int fd = open(SERVER_FIFO,O_WRONLY);
   if(fd == -1)
   {
      printf("服务器 未开启 ！ 连接失败 ！！\n");
      exit(1);
   }   
   c_msg to_server;
   to_server.num = MSG_REGISTER;
   to_server.src.num = info.num;
   strcpy(to_server.src.name,info.name);
   to_server.src.pid = info.pid; 

   cJSON *json_info = struct_to_json(&to_server);
   
   char *msg = cJSON_Print(json_info);
   int len = strlen(msg);
   int ret = write(fd,msg,len);
   if(ret == -1)
   {
      perror("client write error !!");
      exit(1);
   }
   printf("注册消息 发送成功！ret = %d len = %d\n",ret,len);
   close(fd);

}
void OnOffLine()
{
   c_msg to_server;
   to_server.num = MSG_EXIT;
   to_server.src.num = myinfo.info.num;
   strcpy(to_server.src.name, myinfo.info.name);
   to_server.src.pid = myinfo.info.pid;

   SendMsg(SERVER_FIFO ,&to_server);
   printf("发送离线命令给 服务端！！\n");
}

void show(char *str)
{
    printf("info:%s\n",str);

}
void OnMsg(SMP *server_mmap)
{
  	int showHint = 1;
   	while (1)
   	{
    		// printf("消息线程 命令是：%s  status=%d
  	  	// \n",server_mmap->cmd,server_mmap->status);
  	  	if (server_mmap->status == SMP_STOP)
    		{
  	   		sleep(1);
	  	  	return;
	    	}
	    	if (showHint == 1)
	    	{
	   	  	//show("已经连接服务器，开始监听服务端消息...\n");
		    	showHint = 0;
	     	}
	    	// 4非阻塞读私有FIFO
	    	c_msg *cmsg = ReadFifo(fd);

	    	// read返回-1 继续轮询
	    	// read返回>0 协议包解析
    		if (NULL == cmsg)
    		{
    			sleep(1);
    			continue;
    		}
    		showHint = 1;
    		//printf("num = %d  >>>>>>\n\n", cmsg->num);
    		// num为1 聊天信息解析 打印到输出端聊天信息
    		// // num为2 服务端更新在线列表信息 打印到输出端
    		if (cmsg->num == MSG_CHAT)
    		{
    			//收到聊天信息
    			printf("<><><>消息：%s 对 %s 说>> %s \n", cmsg->src.name, cmsg->dest.name, cmsg->msg);
				}
	    	else if (cmsg->num == MSG_ONLINE)
    		{
    			//收到在线列表信息
    			printf("<><><>列表更新：< %s > 用户上线了 num:%d\n", cmsg->dest.name, cmsg->dest.num);
    		}
    		else if (cmsg->num == MSG_OFFLINE)
    		{
    			printf("<><><>列表更新：%s用户下线了 num:%d\n", cmsg->dest.name, cmsg->dest.num);
    		}

		sleep(1);
	}

}
int OnChat(int usrnum,char *context)
{
	  c_msg to_server;
	  to_server.num = MSG_CHAT;
		strcpy(to_server.msg, context);

		to_server.src.num = myinfo.info.num;
		strcpy(to_server.src.name, myinfo.info.name);
		to_server.src.pid = myinfo.info.pid;

		//对方info
		to_server.dest.num = usrnum;
		strcpy(to_server.dest.name, "TODO_NAME");
		to_server.dest.pid = 1000;

		SendMsg(SERVER_FIFO ,&to_server);
		printf("聊天信息，发送成功！usrnum = %d contxt = %s\n",usrnum, to_server.msg);
}
void GetUsrList()
{
   printf("获取用户列表！！！\n");

}
void ShowHelp(int usrid)
{
	  if(usrid == 0)
	  {
		   printf("s 选择聊天对象，l 获取在线用户  quit 退出程序，h 显示帮助信息。 \n");
	  }
	  else
	  {
	    printf("b 返回上一级 ,h 显示帮助信息。");
	  }
}
void OnInput(SMP *server_mmap)
{
	int usrid = 0;
	// 5设置标准输入为非阻塞属性 读标准输入
	// read 返回-1 继续轮询
	// read 返回>1 字符串解析 填充struct c msg
	//向服务器公共FIFO 写msg
	// 6 轮询
	
	printf("输入线程开始工作!!\n");
	while (1) 
  {
  	ShowHelp(usrid);
    scanf("%s",server_mmap->cmd);

		//printf("收到输入 cmd：%s \n",server_mmap->cmd);
		if (strcasecmp(server_mmap->cmd,"quit") == 0 && usrid == 0)
		{
			server_mmap->status = SMP_STOP;
			OnOffLine();
			sleep(1);
			printf("输入线程 收到 停止命令 ！");
			return;
		}
    else if(strcasecmp(server_mmap->cmd,"h") == 0)
    {
      ShowHelp(usrid);
    }
		else if(strcasecmp(server_mmap->cmd,"l") == 0)
		{
		    GetUsrList();
		}
    else if(strcasecmp(server_mmap->cmd,"s") == 0)
    {
      printf("输入用户id 开始聊天 ！！\n");
      scanf("%d", &usrid);

          while(1)
          {
             //printf("当前聊天对象 %d 输入内容发送消息， 或 输入 b  退出当前聊天！\n",usrid);
             scanf("%s",server_mmap->cmd);
             if(strcasecmp(server_mmap->cmd,"b") == 0 ||
             		 strcasecmp(server_mmap->cmd,"quit") == 0)
             {
                printf("已经退出聊天！！\n");
                usrid = 0;
                break;
             }
             else if(strcasecmp(server_mmap->cmd,"h") == 0)
             {
             	 ShowHelp(usrid);
             }
              OnChat(usrid,server_mmap->cmd);
           } 
     }
     else
     {
       printf("无效命令 ！！\n");
     } 

  	}
}


int main(int argc, char *argv[])
{
	// 1 获得自己的pid和 name 填充 struct s msg
	myinfo.info.pid = getpid();
	printf("input your name : ");
	char *input_name[128];
	scanf("%s", input_name);

	strcpy(myinfo.info.name, input_name);

	printf("Hello! %s \n", myinfo.info.name);

	// 2非阻塞属性创建私有FIFO
	GetFifoPath(myinfo.info,fifo_path);

	fd = Init_fifo(fifo_path);

	// 3打开服务器公共FIFO，把自己的信息向服务器注册
	OnRegister(myinfo.info);

	//开两个线程 一个处理服务端的消息
	//一个 处理用户输入 和发送给服务端

	// smp
	SMP *server_mmap;  //匿名映射
	server_mmap = (SMP *)mmap(NULL, sizeof(SMP), PROT_READ | PROT_WRITE,
				  MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (server_mmap == MAP_FAILED) {
		perror("mmap error !!");
		exit(1);
	}
	server_mmap->status = SMP_START;  //运行状态

	pid_t msg_pid;
	pid_t input_pid;

	msg_pid = fork();
	if (msg_pid == -1) {
		perror("fork msg pid error !!");
		exit(1);
	}
	else if (msg_pid == 0) {
		OnMsg(server_mmap);
		return 0;
	}

	input_pid = fork();
	if (input_pid == -1) {
		perror("fork input pid error !!");
		exit(1);
	}
	else if (input_pid == 0) {
		OnInput(server_mmap);
		return 0;
	}

	while (1) {
		if(server_mmap->status == SMP_STOP)
		{
			break;
		}
		// printf("主线程 命令是：%s \n",server_mmap->cmd);
		sleep(1);
	}

	// printf("主线城 开始回收 子线程！！！");
	waitpid(msg_pid, NULL, 0);  // WNOHANG 非阻塞 0 阻塞
	waitpid(input_pid, NULL, 0);


	Deinit_fifo(fd);
	munmap(server_mmap, sizeof(SMP));

	// OnExit(myinfo.info);
	//sleep(3);
	remove(fifo_path);
	// unlink(fifo_path);
	return 0;
}
