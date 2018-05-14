#include <sys/types.h>
#include <sys/stat.h>
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
#include "chat_fifo.h"
#include "s2j.h"

int Init_fifo(char *name)
{
	 int ret = 0;
   //建立管道
   if(access(name,F_OK) == -1)
   {
     ret = mkfifo(name,0777);
     if(ret == -1)
     {
     	 perror("mkfifo error !!");
     	 exit(1);
     }
   }

   int fd = open(name,O_RDONLY | O_NONBLOCK);
   if(fd == -1)
   {
      perror("open fifo error !");
      exit(1);
   }
	 //printf("init fifo name = %s , fd = %d",name,fd);
   return fd;
}
int Deinit_fifo(int fd)
{
   int ret = close(fd);
   if(ret == -1)
   {
      perror("close fd error !!!\n");
   }
   return ret;
}
c_msg *ReadFifo(int fd)
{
   //printf("start readfifo !fd=%d  num = %d\n",fd,numm);
   int len = sizeof(c_msg);
   char buf[len];
   memset(buf,0,len);
   int ret = read(fd,buf,sizeof(buf));
   //printf("read fd >> ret = %d  !fd=%d  num = %d\n",ret, fd,numm);
   if(ret == -1)
   {
   	 //perror("read error !!");
   	 //exit(1);
   	 return NULL;
   }
   else if(ret == 0)
   {
      return NULL;
   }
   //printf("read buf : %s\n<><><><><><><><>\n",buf);
   cJSON *json_obj = cJSON_Parse(buf);
   return (c_msg *)json_to_struct(json_obj);
}


void *json_to_struct(cJSON* json_obj) {
	    /* 创建Student结构体对象 */
	   s2j_create_struct_obj(struct_c_msg, c_msg);

	        /* 反序列化数据到Student结构体对象 */
	        s2j_struct_get_basic_element(struct_c_msg, json_obj, int, num);
	        s2j_struct_get_basic_element(struct_c_msg, json_obj, string, msg);

	                        /* 反序列化数据到Student.Hometown结构体对象 */

	                        s2j_struct_get_struct_element(struct_src, struct_c_msg, json_src, json_obj, my_usr, src);
	                            s2j_struct_get_basic_element(struct_src, json_src, int, num);
	                            s2j_struct_get_basic_element(struct_src, json_src, string, name);
	                            s2j_struct_get_basic_element(struct_src, json_src, int, pid);

	                        s2j_struct_get_struct_element(struct_dest, struct_c_msg, json_dest, json_obj, my_usr, dest);
	                            s2j_struct_get_basic_element(struct_dest, json_dest, int, num);
	                            s2j_struct_get_basic_element(struct_dest, json_dest, string, name);
	                            s2j_struct_get_basic_element(struct_dest, json_dest, int, pid);

	                                /* 返回Student结构体对象指针 */
	                                return struct_c_msg;
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

int SendMsg(char *fifo_path,c_msg *to_msg)
{
	int fd = open(fifo_path, O_WRONLY);
	if (fd == -1) {
		printf("fifo文件 未能打开 ！无法发送消息 ！！\n");
		exit(1);
	}
	cJSON *json_info = struct_to_json(to_msg);

	char *msg = cJSON_Print(json_info);
	int len = strlen(msg);
	int ret = write(fd, msg, len);
	if (ret == -1) {
		perror("fifo  write error !!");
		exit(1);
	}
  //printf("SendMsg content = %s",msg); 
	return 0;

}


void GetFifoPath(my_usr info,char *fifo_path)
{
    strcpy(fifo_path, "../");                                               
    strcat(fifo_path, info.name);
    strcat(fifo_path, "_");
    char *num[32];
    sprintf(num, "%d", info.pid);
    strcat(fifo_path, num);
}


















