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
 	ev->events = 0;
 	ev->arg = NULL;
 	ev->status = 0;
 	//memset(ev->buf,0,sizeof(ev->buf));
 	evbuffer_free(ev->buf);
 	ev->len = 0;
 	ev->last_active = 0;   
}
myevent_s *myevent_new(int fd,void * arg)
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

	struct myevent_s *ev = &g_events[i];
	ev->fd = fd;
    ev->call_back = recv_data;
    ev->events = 0;
    ev->arg = arg;
    ev->status = 1;
    ev->len = 0;
    ev->last_active = time(NULL);
    //ev->buf = evbuffer_new();

    return ev;
}
void recv_data(void *arg)
{
	printf("recvttt>>>>>>>>\n");
	printf("start recv data !!! >>>\n");
	struct myevent_s *ev = (struct myevent_s *)arg;
	struct bufferevent *bev = (struct bufferevent *)ev->arg;
	bufferevent_lock(bev);

	if(bev->input == NULL)
	{
		printf("input is null >>\n");
	}
	return;
	evbuffer_lock(bev->input);
	struct evbuffer *evbuf = bufferevent_get_input(bev);
	int ret = evbuffer_remove(evbuf,ev->buf,BUFSIZ);
	if(ret == -1)
	{
		printf("evbuffer_remove error!!\n");
		return;
	}
 	//   printf("fd=%u, read line: %s\n", fd, ev->buf);
	//	ev->len = strlen(ev->buf);
	bufferevent_disable(bev,EV_READ);
    bufferevent_enable(bev,EV_WRITE);
    evbuffer_unlock(bev->input);
    bufferevent_unlock(bev);
	return;
    //bufferevent_write(bev, line, n);
}
void send_data(void *arg)
{
	printf("start send data !!>>>");
	struct myevent_s *ev = (struct myevent_s *)arg;
	struct bufferevent *bev = (struct bufferevent *)ev->arg;

    bufferevent_write(bev, ev->buf, ev->len);
    evutil_socket_t fd = bufferevent_getfd(bev);
	printf("on send data fd:%d,len:%d\n",fd,ev->len);

	bufferevent_disable(bev,EV_WRITE);
    bufferevent_enable(bev,EV_READ);
}
