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

#include "../include/threadpool.h"
#include "../include/eventepoll.h"

int g_efd;
struct myevent_s g_events[MAX_EVENTS+1];
void eventset(struct myevent_s *ev,int fd,void (*call_back)(int,int,void *),void *arg)
{
	ev->fd = fd;
	ev->call_back = call_back;
	ev->events = 0;
	ev->arg = arg;
	ev->status = 0;
	memset(ev->buf,0,sizeof(ev->buf));
	ev->len = 0;
	ev->last_active = time(NULL);
}

void eventadd(int efd,int events,struct myevent_s *ev)
{
	struct epoll_event epv = {0,{0}};
	int op;
	epv.data.ptr = ev;
	epv.events = ev->events = events;

	if(ev->status == 1)
	{
		op = EPOLL_CTL_MOD;
	}
	else
	{
		op = EPOLL_CTL_ADD;
		ev->status = 1;
	}

	int ret = epoll_ctl(efd,op,ev->fd,&epv);
	if(ret < 0)
	{
		printf("event add failed [fd=%d] , op=%d, events[%d]\n",ev->fd,op,events);
	}
	else
	{
		printf("event add OK [fd=%d] , op=%d, events[%d]\n",ev->fd,op,events);
	}

}

void eventdel(int efd,struct myevent_s *ev)
{
	struct epoll_event epv = {0,{0}};

	if(ev->status != 1)
	{
		return;
	}

	epv.data.ptr = ev;
	ev->status = 0;
	epoll_ctl(efd,EPOLL_CTL_DEL,ev->fd,&epv);
}

void senddata(int fd,int events,void *arg)
{
	struct myevent_s *ev = (struct myevent_s *)arg;
	int len;

	len = send(fd,ev->buf,ev->len,0);  // 直接将 数据 写回 客户端 

	//printf("fd=%d\t ev->buf=%s\t ev->len=%d\n",fd,ev->buf,ev->len);
	//printf("send len = %d\n",len);

	if(len > 0)
	{
		printf("send[fd=%d], [%d]\t%s\n",fd,len,ev->buf);
		eventdel(g_efd,ev);
		eventset(ev,fd,recvdata,ev);
		eventadd(g_efd,EPOLLIN,ev);
	}
	else
	{
		close(ev->fd);
		eventdel(g_efd,ev);
		printf("send[fd=%d] len[%d], error %s\n",fd,len,strerror(errno));
	}
}
void recvdata(int fd,int events, void *arg)
{
	struct myevent_s *ev = (struct myevent_s *)arg;
	int len;

	len = recv(fd,ev->buf,sizeof(ev->buf),0); // 读文件 描述符 数据 存入myevents buf

	eventdel(g_efd,ev);

	if(len > 0)
	{
		ev->len = len;
		ev->buf[len] = '\0';
		printf("C[%d]:%s\n",fd,ev->buf);

		ev->fd = fd;
		ev->call_back = senddata;
		ev->events = 0;
		ev->arg = arg;
		ev->status = 0;
		ev->last_active = time(NULL);

		//eventset(ev,fd,senddata,ev);
		eventadd(g_efd,EPOLLOUT,ev);
	}
	else if(len == 0)
	{
		close(ev->fd);
		printf("[fd=%d] pos[%ld],closed\n",fd,ev-g_events);
	}
	else
	{
		close(ev->fd);
		printf("recv[fd=%d] error[%d]:%s\n",fd,errno,strerror(errno));
	}
}

void acceptconn(int lfd,int events,void *arg)
{
	struct sockaddr_in cin;
	socklen_t len = sizeof(cin);
	int cfd,i;

	cfd = accept(lfd,(struct sockaddr *)&cin,&len);
	if(cfd == -1)
	{
		if(errno != EAGAIN && errno != EINTR)
		{
			// 暂时不座 出错处理
		}

		printf("%s:accept, %s\n",__func__,strerror(errno));
		return;
	}

	do
	{
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
			break;
		}

		int flag = fcntl(cfd,F_SETFL,O_NONBLOCK);
		if(flag < 0)
		{
			printf("%s:fcntl nonblocking failed, %s\n",__func__,strerror(errno));
			break;
		}

		eventset(&g_events[i],cfd,recvdata,&g_events[i]);
		eventadd(g_efd,EPOLLIN,&g_events[i]);
	}
	while(0);

	printf("new connect [%s:%d] [time:%ld], pos[%d]\n",inet_ntoa(cin.sin_addr),ntohs(cin.sin_port),g_events[i].last_active,i);
}

void initlistensocket(int efd,short port)
{
	int lfd = socket(AF_INET,SOCK_STREAM,0);
	fcntl(lfd,F_SETFL,O_NONBLOCK);

	eventset(&g_events[MAX_EVENTS],lfd,acceptconn,&g_events[MAX_EVENTS]);

	eventadd(efd,EPOLLIN,&g_events[MAX_EVENTS]);

	struct sockaddr_in sin;
	memset(&sin,0,sizeof(sin));

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);

	bind(lfd,(struct sockaddr *)&sin,sizeof(sin));

	listen(lfd,128);
}
int Epoll_Start(int argc, char *argv[],threadpool_t *thp)
{
	unsigned short port = SERV_PORT;

	if(argc == 2)
	{
		port = atoi(argv[1]);
	}

	g_efd = epoll_create(MAX_EVENTS + 1);
	if(g_efd <= 0)
	{
		printf("create efd in %s err %s\n",__func__,strerror(errno));
	}

	initlistensocket(g_efd,port);

	struct epoll_event events[MAX_EVENTS+1];
	printf("server running:port[%d]\n",port);

	int checkpos = 0,i;
	while(1)
	{
		//超时验证 每次 测试 100 个连接 当客户端 60妙无通讯 踢出客户端

		long now = time(NULL);
		for(i=0;i<100;i++,checkpos++)
		{
			if(checkpos == MAX_EVENTS)
			{
				checkpos = 0;
			}
			if(g_events[checkpos].status != 1)
			{
				continue;
			}

			long duration = now - g_events[checkpos].last_active;

			if(duration >= 60)
			{
				close(g_events[checkpos].fd);
				printf("[fd=%d] timeout\n",g_events[checkpos].fd);
				eventdel(g_efd,&g_events[checkpos]);
			}
		}//for end

		// 返回 n个 fd 事件
		int nfd = epoll_wait(g_efd,events,MAX_EVENTS+1,1000);
		if(nfd < 0)
		{
			printf("epoll wait error, exit\n");
			break;
		}

		for(i=0;i<nfd;i++)
		{
			struct myevent_s *ev = (struct myevent_s *)events[i].data.ptr;

			if((events[i].events & EPOLLIN) && (ev->events & EPOLLIN))
			{
				struct myevent_s *myev = (struct myevent_s *)malloc(sizeof(struct myevent_s));
				//memcpy(myev,ev,sizeof(myevent_s));
				myev->fd = ev->fd;
				myev->call_back = ev->call_back;
				myev->events = events[i].events;
				printf("threadpool add fd:%d,evnets:%d\n",myev->fd,myev->events);
				threadpool_add(thp,process_event,(void *)myev);
				//ev->call_back(ev->fd,events[i].events,ev->arg);
			}
			if((events[i].events & EPOLLOUT) && (ev->events & EPOLLOUT))
			{
				struct myevent_s *myev = (struct myevent_s *)malloc(sizeof(struct myevent_s));
				//memcpy(myev,ev,sizeof(myevent_s));
				myev->fd = ev->fd;
				myev->call_back = ev->call_back;
				myev->events = events[i].events;
				threadpool_add(thp,process_event,(void *)myev);
				//ev->call_back(ev->fd,events[i].events,ev->arg);
			}
		}



	}//while end

	return 0;
}
