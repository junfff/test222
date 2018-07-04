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
struct myevent_s g_events[MAX_EVENTS+1];
threadpool_t *thp;
void eventset(struct myevent_s *ev,void (*call_back)(struct bufferevent *,void *),void *arg)
{
    ev->call_back = call_back;
    ev->arg = arg;
    ev->last_active = time(NULL);
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
    ev->call_back = NULL;
    ev->events = 0;
    ev->arg = arg;
    ev->status = 0;
    memset(ev->buf,0,sizeof(ev->buf));
    ev->len = 0;
    ev->last_active = time(NULL);

    return ev;
}
void readdata(struct bufferevent *bev,void *arg)
{
    char line[MAX_LINE+1];
    int n;
    evutil_socket_t fd = bufferevent_getfd(bev);

    while (n = bufferevent_read(bev, line, MAX_LINE), n > 0) {
        line[n] = '\0';
        printf("fd=%u, read line: %s\n", fd, line);

        bufferevent_write(bev, line, n);
    }
}
