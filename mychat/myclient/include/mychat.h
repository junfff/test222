#ifndef _MY_CHAT_H_
#define _MY_CHAT_H_
//0 新用户注册
//1 聊天信息
//2 服务器更新列表信息
#include <sys/types.h>
#include <unistd.h>

#define SERVER_FIFO "../server_fifo"
#define MSG_REGISTER 1
#define MSG_CHAT 2
#define MSG_EXIT 3
#define SMP_START 1
#define SMP_STOP 0
#define BUF_MAX 1024
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

typedef struct
{
  int status;
  char cmd[BUF_MAX];
}SMP;
#endif
