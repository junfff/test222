#include <sys/types.h>
#include "s2j.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "mychat.h"
#include <unistd.h>


void CreatorClientFifo(char *path)
{
   int ret = mkfifo(path,0777);
   if(ret == -1)
   {
      perror("client mkfifo error !! ");
      exit(1);
   }
}

cJSON *struct_to_json(void* struct_obj) {
	    c_msg *struct_student = (c_msg *)struct_obj;
	        
	        /* create Student JSON object */
	        s2j_create_json_obj(json_student);
		    
		    /* serialize data to Student JSON object. */
		    s2j_json_set_basic_element(json_student, struct_student, int, num);
		    
				    /* serialize data to Student.Hometown JSON object. */
				    s2j_json_set_struct_element(json_hometown, json_student, struct_hometown, struct_student, my_usr, src);
				        s2j_json_set_basic_element(json_hometown, struct_hometown, int, num);
				        s2j_json_set_basic_element(json_hometown, struct_hometown, string, name);
				        s2j_json_set_basic_element(json_hometown, struct_hometown, int, pid);

				    s2j_json_set_struct_element(json_dest, json_student, struct_dest, struct_student, my_usr, dest);
				        s2j_json_set_basic_element(json_dest, struct_dest, int, num);
				        s2j_json_set_basic_element(json_dest, struct_dest, string, name);
				        s2j_json_set_basic_element(json_dest, struct_dest, int, pid);

			        s2j_json_set_basic_element(json_student, struct_student, string, msg);
				    
					    
					    /* return Student JSON object pointer */
					    return json_student;

}
void OnRegister(my_usr info)
{
   int fd = open(SERVER_FIFO,O_WRONLY);
   if(fd == -1)
   {
      printf("服务器 未开启 ！ 连接失败 ！！");
      exit(1);
   }   
   c_msg to_server;
   to_server.num = MSG_REGISTER;
   to_server.src.num = info.num;
   strcpy(to_server.src.name,info.name);
   to_server.src.pid = info.pid; 

   cJSON *json_info = struct_to_json(&to_server);
   
   char *msg = cJSON_Print(json_info);
   int ret = write(fd,msg,sizeof(msg));
   if(ret == -1)
   {
      perror("client write error !!");
      exit(1);
   }
   printf("注册消息 发送成功！\n");

}

int main(int argc,char *argv[])
{
   //1 获得自己的pid和 name 填充 struct s msg
   s_msg myinfo;
   myinfo.info.pid = getpid();
   printf("input your name : ");
   char *input_name[128];
   scanf("%s",input_name);

   strcpy(myinfo.info.name,input_name);
   
   printf("Hello! %s \n",myinfo.info.name);

   //2非阻塞属性创建私有FIFO
   char fifo_path[128];
   strcpy(fifo_path,"../");
   strcat(fifo_path,myinfo.info.name);
   strcat(fifo_path,"_");
   strcat(fifo_path,myinfo.info.pid);
   
   CreatorClientFifo(fifo_path);

   //3打开服务器公共FIFO，把自己的信息向服务器注册
   OnRegister(myinfo.info);


   //4非阻塞读私有FIFO
   //read返回-1 继续轮询
   //read返回>0 协议包解析
   //num为1 聊天信息解析 打印到输出端聊天信息
   //num为2 服务端更新在线列表信息 打印到输出端
   //5设置标准输入为非阻塞属性 读标准输入
   //read 返回-1 继续轮询
   //read 返回>1 字符串解析 填充struct c msg
   //向服务器公共FIFO 写msg
   //6 轮询




   unlink(fifo_path);
   return 0;
}
