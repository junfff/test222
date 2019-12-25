/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：epoll.c
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年06月18日 11:52(Monday) 
 *   描    述：
 *
 ================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>
#include <ctype.h>
#include <fcntl.h>

#include "wrap.h"

#define MAXLINE 8192
#define SERV_PORT 33000
#define OPEN_MAX 5000

typedef int(*CallBack)(int fd,void *argv);
typedef struct ep_Info
{
	int fd;
	void *argv;
	CallBack func;
}ep_Info;
typedef struct serv_Info
{
	int efd;
	int num;
}serv_Info;

int OnReceived(int fd,void *argv)
{
	serv_Info *sInfo = (serv_Info *)argv;
	int res,n;
	char buf[MAXLINE];
	// 非阻塞轮询 读取数据
	//while((n = Read(fd,buf,MAXLINE/2)) > 0)
	//{
	//}
	n = Read(fd,buf,MAXLINE);
	if(n == 0)
	{
		res = epoll_ctl(sInfo->efd,EPOLL_CTL_DEL,fd,NULL);
		if(res == -1)
		{
			printf("epoll ctl del error");
			return -1;
		}
		Close(fd);
		printf("client[%d] closed connection\n",fd);
		return 1;
	}
	else if(n < 0)
	{
		perror("read n < 0 error");
		res = epoll_ctl(sInfo->efd,EPOLL_CTL_DEL,fd,NULL);
		Close(fd);
		return -2;
	}
	else
	{
		for(int j=0;j<n;j++)
		{
			buf[j] = toupper(buf[j]);
		}
		Write(STDOUT_FILENO,buf,n);
		Write(fd,buf,n);
	}
	return 0;
}
int OnLink(int fd,void *argv)
{
	serv_Info *sInfo = (serv_Info *)argv;
	char str[INET_ADDRSTRLEN];
	sockaddr_in cliaddr;
	socklen_t clilen = sizeof(cliaddr);
	int connfd = Accept(fd,(struct sockaddr *)&cliaddr,&clilen);

	printf("received from %s at PORT %d\n",
				inet_ntop(AF_INET,&cliaddr.sin_addr,str,sizeof(str)),
				ntohs(cliaddr.sin_port));

	printf("cfd %d---client %d\n",connfd,++(sInfo->num));

	//修改connfd为 非阻塞读
	//int flag = fcntl(connfd,F_GETFL);
	//flag |= O_NONBLOCK;
	//fcntl(connfd,F_SETFL,flag);

	ep_Info *cInfo = (ep_Info *)malloc(sizeof(ep_Info));
	cInfo->fd = connfd;
	cInfo->func = OnReceived;
	cInfo->argv = argv;
	struct epoll_event tep;
	tep.events = EPOLLIN;   // EPOLLET 边沿触发  EPOLLLT 水平出发  ET 非阻塞 性能up
	tep.data.ptr = (void *)cInfo;
	int res = epoll_ctl(sInfo->efd,EPOLL_CTL_ADD,connfd,&tep);
	if(res == -1)
	{
		perr_exit("on add client fd epoll ctl error");
	}

	return 0;
}
int main()
{
	serv_Info sInfo;

	int i,listenfd;
	ssize_t nready,res;

	struct sockaddr_in servaddr;
	struct epoll_event tep,ep[OPEN_MAX]; //tep epoll ctl参数 ep[] epoll_wait参数
	listenfd = Socket(AF_INET,SOCK_STREAM,0);

	int opt = 1;
	setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);

	Bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

	Listen(listenfd,128);

	sInfo.efd = epoll_create(OPEN_MAX); //创建红黑树 树根
	if(sInfo.efd == -1)
	{
		perr_exit("epoll create error");
	}

	ep_Info *info_link = (ep_Info *)malloc(sizeof(ep_Info));
	info_link->fd = listenfd;
	info_link->func = OnLink;
	info_link->argv = (void *)&sInfo;
	tep.events = EPOLLIN;
	tep.data.ptr =(void *)info_link;
	res = epoll_ctl(sInfo.efd,EPOLL_CTL_ADD,listenfd,&tep);
	if(res == -1)
	{
		perr_exit("epoll ctl error");
	}

	while(1)
	{
		nready = epoll_wait(sInfo.efd,ep,OPEN_MAX,-1);
		if(nready == -1)
		{
			perr_exit("epoll wait error");
		}

		for(i=0;i<nready;i++)
		{
			if(!(ep[i].events & EPOLLIN))
			{
				continue;
			}
			ep_Info *tmp = (ep_Info *)ep[i].data.ptr;
			if(tmp->func)
			{
				res = tmp->func(tmp->fd,tmp->argv);
				if(res != 0)
				{
					free(tmp);
					if(res < 0)
					{
						perr_exit("on tmp func error ");
					}
				}
			}
			else
			{
				printf("on tmp func is null fd:%d \n",tmp->fd);
			}

		}

	}
	free(info_link);
	Close(listenfd);
	Close(sInfo.efd);

	return 0;
}
