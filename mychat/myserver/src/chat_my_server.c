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
#include "chat_my_server.h"
#include "s2j.h"

int fd;

int Init(char *name)
{
   int ret;
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

   
   fd = open(name,O_RDONLY);
   if(fd == -1)
   {
      perror("open fifo error !");
      exit(1);
   }

   printf("open fifo succeed !\n");

   return ret;
}
c_msg *ReadFifo()
{
   int len = sizeof(c_msg);
   char buf[len];
   memset(buf,0,len);
   int ret = read(fd,buf,sizeof(buf));
   if(ret == -1)
   {
   	 perror("read error !!");
   	 exit(1);
   }

   cJSON *json_obj = cJSON_Parse(buf);

   return (c_msg *)json_to_struct(json_obj);
}


void *json_to_struct(cJSON* json_obj) {
	    /* 创建Student结构体对象 */
	   s2j_create_struct_obj(struct_c_msg, c_msg);

	        /* 反序列化数据到Student结构体对象 */
	        s2j_struct_get_basic_element(struct_c_msg, json_obj, int, num);

	                        /* 反序列化数据到Student.Hometown结构体对象 */

	                        s2j_struct_get_struct_element(struct_src, struct_c_msg, json_src, json_obj, my_usr, src);
	                            s2j_struct_get_basic_element(struct_src, json_src, int, num);
	                            s2j_struct_get_basic_element(struct_src, json_src, string, name);
	                            s2j_struct_get_basic_element(struct_src, json_src, int, pid);

	                        s2j_struct_get_struct_element(struct_dest, struct_c_msg, json_dest, json_obj, my_usr, dest);
	                            s2j_struct_get_basic_element(struct_dest, json_dest, int, num);
	                            s2j_struct_get_basic_element(struct_dest, json_dest, string, name);
	                            s2j_struct_get_basic_element(struct_dest, json_dest, int, pid);

	            s2j_struct_get_array_element(struct_c_msg, json_obj, string, msg);
	                                /* 返回Student结构体对象指针 */
	                                return struct_c_msg;
}























