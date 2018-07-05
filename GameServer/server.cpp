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
#include "./include/myevents.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <event.h>
#include <fcntl.h>
#include <assert.h>
#include <event2/thread.h>



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


void read_cb(struct bufferevent *bev,void *arg)
{
	printf("start read cb \n");
	myevent_s *ev = (myevent_s *)bev->cbarg;
	if(ev == NULL)
	{
		printf("bev ev is NULL!!!");
		return;
	}

	struct evbuffer *input = bufferevent_get_input(bev);
	if(input == NULL)
	{
		printf("bev input is NULL!!!");
		return;
	}
	evbuffer_add_buffer(ev->buf,input);
	if(NULL != ev->buf)
	{
		printf("ev buf not null !!\n");
	}
	else
	{
		printf("buf is null !!!\n");
	}
	return;
	eventset(ev, recv_data,bev);

 	threadpool_add(thp,process_event,(void *)bev);
    // bufferevent_write(bev, line, n);

}

void write_cb(struct bufferevent *bev,void *arg)
{
	printf("start write cb\n");
	myevent_s *ev = (myevent_s *)arg;
	eventset(ev,send_data,arg);
 	threadpool_add(thp,process_event,(void *)arg);
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

    myevent_free(bev->cbarg);
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

	evutil_make_socket_nonblocking(fd);

    struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_THREADSAFE | BEV_OPT_CLOSE_ON_FREE);
	if(NULL == bev)
	{
		printf("bufferevent new error!!");
		close(fd);
		return;
	}
	myevent_s *mev = myevent_new(fd,bev);
	if(NULL == mev)
	{
		printf("myevent new error!!");
		close(fd);
		bufferevent_free(bev);
		return;
	}
	bev->cbarg = mev;
	//evbuffer_enable_locking(bev->output,NULL);
	//evbuffer_enable_locking(bev->input,NULL);
    bufferevent_setcb(bev, read_cb, write_cb, error_cb, bev);
    bufferevent_enable(bev, EV_PERSIST | EV_READ);
    printf("ACCEPT: fd = %u\n", fd);
}

int main(int argc,char *argv[])
{
	thp = threadpool_create(3,100,100); // 创建 线程  最小线程，最大，队列最大
	printf("pool inited\n");

    //Epoll_Start(argc,argv,thp);

	evthread_use_pthreads();
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
