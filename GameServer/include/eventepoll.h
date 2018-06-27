/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：eventepoll.h
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年06月27日 16:39(Wednesday) 
 *   描    述：
 *
 ================================================================*/


#pragma once
#include "threadpool.h"

#define MAX_EVENTS 1024
#define BUFLEN 4096
#define SERV_PORT 33000

struct myevent_s
{
	int fd;
	int events;
	void *arg;
	void (*call_back)(int fd,int events,void *arg);
	int status;
	char buf[BUFLEN];
	int len;
	long last_active;
};

extern int g_efd;
extern struct myevent_s g_events[MAX_EVENTS+1];

void recvdata(int fd,int events,void *arg);
void senddata(int fd,int events,void *arg);
int Epoll_Start(int argc, char *argv[],threadpool_t *thp);
