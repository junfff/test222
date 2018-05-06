#ifndef _MY_CHAT_H_
#define _MY_CHAT_H_
//0 新用户注册
//1 聊天信息
//2 服务器更新列表信息
#include <sys/types.h>
#include <unistd.h>

#define SERVER_FIFO "server_fifo"

typedef struct
{
   int num;
   char name[10];
   int pid;
}my_usr;

typedef struct
{
   int num;
   my_usr src;
   my_usr dest;
   char msg[256];
}c_msg;

typedef struct
{
   int num;
   my_usr info;
}s_msg;

#endif