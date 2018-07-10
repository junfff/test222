/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：myevents.hpp
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年07月10日 16:25(Tuesday) 
 *   描    述：
 *
 ================================================================*/


#ifndef _MYEVENTS_H
#define _MYEVENTS_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "threadpool.hpp"
#include "MarshalEndian.hpp"
#include "Base/MoudlesCollection.hpp"
	using namespace GameBase;

#define MAX_EVENTS 1024
#define BUFLEN 4096
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
		char buf[BUFLEN+1];
		int len;
		long last_active;

		MoudlesCollection *coreMoudles;
	};

	extern struct event_base *g_base;
	extern  threadpool_t *thp;
	extern struct myevent_s g_events[MAX_EVENTS+1];//声明

	void recv_data(void *arg);
	void send_data(void *arg);

	void myevent_free(void *);
	myevent_s *myevent_new(int fd,struct event_base *base,MoudlesCollection *moudlesMgr);
	void eventset(struct myevent_s *ev,void (*call_back)(void *),void *arg);
#ifdef __cplusplus
}
#endif
#endif //MYEVENTS_H
