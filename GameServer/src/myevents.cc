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
 	bufferevent_free(ev->bev);
}
myevent_s *myevent_new(int fd,struct event_base *base)
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
    			BEV_OPT_THREADSAFE | BEV_OPT_CLOSE_ON_FREE | BEV_OPT_DEFER_CALLBACKS);
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

    return ev;
}
void recv_data(void *arg)
{
	//printf("start recv data !!! >>>\n");
	struct myevent_s *ev = (struct myevent_s *)arg;
	struct bufferevent *bev = (struct bufferevent *)ev->bev;
	bufferevent_lock(bev);

 	printf(">>>>> on recv fd=%u,len:%d, read : %s\n", ev->fd, ev->len,ev->buf);
	for(int i =0;i<ev->len;i++)
	{
		ev->buf[i] = toupper(ev->buf[i]);
	}

    bufferevent_unlock(bev);

	eventset(ev,send_data,arg);
 	threadpool_add(thp,process_event,(void *)arg);
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
