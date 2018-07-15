/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：eventepoll.c
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年06月23日 19:52(Saturday) 
 *   描    述：
 *
 ================================================================*/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/epoll.h>
#include <event.h>
#include <ctype.h>

#include "../include/threadpool.h"
#include "../include/myevents.h"
#include "../include/MarshalEndian.h"

struct event_base *g_base; 
threadpool_t *thp;
struct myevent_s g_events[MAX_EVENTS+1];//定义

void eventset(struct myevent_s *ev,void (*call_back)(void *),void *arg)
{
    ev->call_back = call_back;
    ev->arg = arg;
    ev->last_active = time(NULL);
}

void myevent_free(void *arg)
{
	struct myevent_s *ev = (struct myevent_s *)arg;
	if(NULL == ev)
	{
		return;
	}

    ev->fd = 0;
 	ev->call_back = NULL;
 	//ev->events = 0;
 	ev->arg = NULL;
 	ev->status = 0;
 	ev->len = 0;
 	ev->last_active = 0;   
 	memset(ev->buf,0,sizeof(ev->buf));
 	ev->Ime->Dispose();
 	delete ev->Ime;
 	ev->coreModules = NULL;

 	bufferevent_free(ev->bev);
}
myevent_s *myevent_new(int fd,struct event_base *base,ModulesCollection *modulesMgr)
{
	int i;
    for(i=0;i<MAX_EVENTS;i++)
    {
        if(g_events[i].status == 0)
        {
            break;
        }
    }
    if(i == MAX_EVENTS)
    {
        printf("%s: max connect limit[%d]\n",__func__,MAX_EVENTS);
        return NULL;
    }

    struct bufferevent *bev = bufferevent_socket_new(base, fd,
    			BEV_OPT_CLOSE_ON_FREE | BEV_OPT_THREADSAFE | BEV_OPT_DEFER_CALLBACKS);
	if(NULL == bev)
	{
		printf("bufferevent new error!!");
		return NULL;
	}
	struct myevent_s *ev = &g_events[i];
	ev->fd = fd;
    ev->call_back = recv_data;
    //ev->events = 0;
    ev->arg = NULL;
    ev->status = 1;
    ev->len = 0;
    ev->last_active = time(NULL);
 	memset(ev->buf,0,sizeof(ev->buf));
 	ev->bev = bev;
 	ev->Ime = new MarshalEndian();
 	ev->Ime->Initialize();
 	ev->Ime->SetContext(ev);
 	ev->Ime->SetCoreModules(modulesMgr);

 	ev->coreModules = modulesMgr;

    return ev;
}
void recv_data(void *arg)
{
	int ret;
	//printf("start recv data !!! >>>\n");
	struct myevent_s *ev = (struct myevent_s *)arg;
	struct bufferevent *bev = (struct bufferevent *)ev->bev;


	bufferevent_lock(bev);
	evbuffer_lock(bev->input);

	struct evbuffer *input = bufferevent_get_input(bev);
	if(input == NULL)
	{
		printf("input is null !!!>>>>>>>>>>>>>>>>>>\n");
		evbuffer_unlock(bev->input);
    	bufferevent_unlock(bev);
		return;
	}
	ret = evbuffer_get_length(input);
	if(ret <= 0)
	{
		printf(">>>没有可读内容 ret:%d\n",ret);
		evbuffer_unlock(bev->input);
    	bufferevent_unlock(bev);
		return;
	}

    //开始读取内容
	ev->len = evbuffer_remove(input,ev->buf,BUFSIZ);
	ev->buf[ev->len] = '\0';
	evbuffer_unlock(bev->input);


	if(ev->len == 1 && ev->buf[0] == '\n')
	{
	    ret = evbuffer_get_length(input);
    	bufferevent_unlock(bev);
		printf(">>>len == 1 buf == /n  ret:%d\n",ret);
		bufferevent_trigger_event(bev,BEV_EVENT_ERROR,1);
		return;
	}
 	printf(">>>>> on recv fd=%u,len:%d, read : %s\n", ev->fd, ev->len,ev->buf);

	ret = ev->Ime->Decode(ev->buf,ev->len);
	if(ret != 0)
	{
		printf("imarshalEndian error !! ret = %d\n",ret);
		bufferevent_trigger_event(bev,BEV_EVENT_ERROR,1);
	}

    bufferevent_unlock(bev);
}

void send_data(void *arg)
{
	//printf(">>>>>>>.  start send data !!>>>\n");
	struct myevent_s *ev = (struct myevent_s *)arg;
	struct bufferevent *bev = (struct bufferevent *)ev->bev;

	bufferevent_lock(bev);

    bufferevent_write(bev, ev->buf, ev->len);

    bufferevent_unlock(bev);

    evutil_socket_t fd = bufferevent_getfd(bev);
	printf(">>>>>>  on send data fd:%d,len:%d\n",fd,ev->len);

}
