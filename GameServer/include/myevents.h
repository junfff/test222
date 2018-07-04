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
#include <event.h>

#define MAX_EVENTS 1024
#define BUFLEN 4096
#define SERV_PORT 33000
#define MAX_LINE    256
#define LISTEN_BACKLOG 32 
struct myevent_s
{
	int fd;
	int events;
	void *arg;
	void (*call_back)(struct bufferevent *bev,void *arg);
	int status;
	char buf[BUFLEN];
	int len;
	long last_active;
};

extern struct event_base *g_base;
extern struct myevent_s g_events[MAX_EVENTS+1];
extern  threadpool_t *thp;

void readdata(struct bufferevent *bev,void *ctx);
void writedata(struct bufferevent *bev,void *ctx);

myevent_s *myevent_new(int fd,void *arg);
void eventset(struct myevent_s *ev,void (*call_back)(struct bufferevent *,void *),void *arg);
