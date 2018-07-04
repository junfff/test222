/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：server.cpp
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年06月27日 16:34(Wednesday) 
 *   描    述：
 *
 ================================================================*/
//#include "./include/eventepoll.h"
#include "./include/threadpool.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <event.h>
#include <fcntl.h>
#include <assert.h>

#define SERV_PORT 33000
#define LISTEN_BACKLOG 32
threadpool_t *thp;

evutil_socket_t initlistensocket(int port)
{
	evutil_socket_t lfd;
 	lfd = socket(AF_INET,SOCK_STREAM,0);

 	assert(lfd > 0);
    evutil_make_listen_socket_reuseable(lfd);


    struct sockaddr_in sin;
    memset(&sin,0,sizeof(sin));

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);

    if (bind(lfd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("bind");
        return 1;
    }

    if (listen(lfd, LISTEN_BACKLOG) < 0)
    {
        perror("listen");
        return 1;
    }

    printf ("Listening...\n");

    evutil_make_socket_nonblocking(lfd);

    return lfd;
}

void read_cb(struct bufferevent *bev,void *ctx)
{
 	//threadpool_add(thp,process_event,(void *)bev);

#define MAX_LINE    256
    char line[MAX_LINE+1];
    int n;
    evutil_socket_t fd = bufferevent_getfd(bev);

    while (n = bufferevent_read(bev, line, MAX_LINE), n > 0) {
        line[n] = '\0';
        printf("fd=%u, read line: %s\n", fd, line);

        bufferevent_write(bev, line, n);
    }

}

void write_cb(struct bufferevent *bev,void *ctx)
{
}
void error_cb(struct bufferevent *bev, short event, void *ctx)
{
    evutil_socket_t fd = bufferevent_getfd(bev);
    printf("fd = %u, ", fd);
    if (event & BEV_EVENT_TIMEOUT) {
        printf("Timed out\n"); //if bufferevent_set_timeouts() called
    }
    else if (event & BEV_EVENT_EOF) {
        printf("connection closed\n");
    }
    else if (event & BEV_EVENT_ERROR) {
        printf("some other error\n");
    }
    bufferevent_free(bev);

}


void do_accept(evutil_socket_t listener, short event, void *arg)
{
    struct event_base *base = (struct event_base *)arg;
    evutil_socket_t fd;
    struct sockaddr_in sin;
    socklen_t slen;
    fd = accept(listener, (struct sockaddr *)&sin, &slen);
    if (fd < 0) {
        perror("accept");
        return;
    }
    if (fd > FD_SETSIZE) {
        perror("fd > FD_SETSIZE\n");
        return;
    }

    printf("ACCEPT: fd = %u\n", fd);

    struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, read_cb, write_cb, error_cb, arg);
    bufferevent_enable(bev, EV_READ|EV_WRITE|EV_PERSIST);
}

int main(int argc,char *argv[])
{
	thp = threadpool_create(3,100,100); // 创建 线程  最小线程，最大，队列最大
	printf("pool inited\n");

    //Epoll_Start(argc,argv,thp);
	event_enable_debug_mode();
    struct event_base *base = event_init();
    assert(base != NULL);

   	evutil_socket_t lfd = initlistensocket(SERV_PORT);
   	printf("server lfd = %d \n",lfd);

	struct event *listen_event;
	listen_event = event_new(base,lfd,EV_READ | EV_PERSIST,do_accept,(void *)base);
	event_add(listen_event,NULL);
	event_base_dispatch(base);

	threadpool_destroy(thp);
	printf("server end >>>>>>>>>>>>\n");
	return 0;
}
