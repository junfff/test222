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
#include <stdio.h>
#include "threadpool.h"
#include "Base/ModulesCollection.h"
#include "IMarshalEndian.h"
using namespace GameBase;

#define MAX_EVENTS 1024
#define SERV_PORT 33000
//#define MAX_LINE    256
#define LISTEN_BACKLOG 32 
#define TIME_OUT 30

// 一个客户端绑定一个 myevents
struct myevent_s
{
	int fd;
	struct bufferevent *bev;
	//int events;
	void *arg;
	void (*call_back)(void *arg);
	int status;
	char buf[BUFSIZ+1];
	int len;
	long last_active;
	IMarshalEndian *Ime;

	ModulesCollection *coreModules;
};

extern struct event_base *g_base;
extern  threadpool_t *thp;
extern struct myevent_s g_events[MAX_EVENTS+1];//声明

void recv_data(void *arg);
void send_data(void *arg);

void myevent_free(void *);
myevent_s *myevent_new(int fd,struct event_base *base,ModulesCollection *modulesMgr);
void eventset(struct myevent_s *ev,void (*call_back)(void *),void *arg);
