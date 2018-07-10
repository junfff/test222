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
#include "./include/Interface.h"
#include "./include/Base/GameBase.h"
#include "./include/Base/IModules.h"

using namespace GameBase;


ModulesCollection *moudlesMgr;



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

//已经读取足够的数据
void read_cb(struct bufferevent *bev,void *arg)
{
	//printf("start read cb \n");
	myevent_s *ev = (myevent_s *)arg;
	if(ev == NULL)
	{
		printf("bev ev is NULL!!!");
		return;
	}
	evbuffer_lock(bev->input);
	struct evbuffer *input = bufferevent_get_input(bev);
	int ret = evbuffer_get_length(input);
	if(ret <= 0)
	{
		printf(">>>没有可读内容 ret:%d\n",ret);
		return;
	}
	ev->len = evbuffer_remove(input,ev->buf,BUFSIZ);
	ev->buf[ev->len] = '\0';
	evbuffer_unlock(bev->input);


	if(ev->len == 1 && ev->buf[0] == '\n')
	{
	    ret = evbuffer_get_length(input);
		printf(">>>len == 1 buf == /n  ret:%d\n",ret);
		bufferevent_trigger_event(bev,BEV_EVENT_ERROR,1);
		return;
	}
	eventset(ev, recv_data,arg);

 	threadpool_add(thp,process_event,(void *)arg);
}
//已经写入足够的数据
void write_cb(struct bufferevent *bev, void *ctx)
{
	//printf("start write cb\n");
	//myevent_s *ev = (myevent_s *)bev->cbarg;
}
//发生错误时被调用
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
    else if (event & BEV_EVENT_ERROR)
    {
    	int ret = 0;//TODO
    	bufferevent_write(bev, "Param Error", 11);
        printf("some other error! ret = %d\n",ret);

        return;
    }

    myevent_free(bev->cbarg);

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

	myevent_s *mev = myevent_new(fd,base,moudlesMgr);
	if(NULL == mev)
	{
		printf("myevent new error!!\n");
		close(fd);
		return;
	}


	evbuffer_enable_locking(mev->bev->output,NULL);
	evbuffer_enable_locking(mev->bev->input,NULL);
    bufferevent_setcb(mev->bev, read_cb, NULL, error_cb, mev);
    bufferevent_enable(mev->bev, EV_PERSIST | EV_READ | EV_WRITE);

	struct timeval tv = {TIME_OUT,0};
	bufferevent_set_timeouts(mev->bev,&tv,NULL);
    printf("ACCEPT: fd = %u\n", fd);
}

int main(int argc,char *argv[])
{
	moudlesMgr = new ModulesCollection();
	moudlesMgr->Initialize();

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

	//********************end
	threadpool_destroy(thp);
	moudlesMgr->Dispose();
	delete moudlesMgr;
	printf("server end >>>>>>>>>>>>\n");
	return 0;
}
