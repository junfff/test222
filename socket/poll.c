/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：poll.c
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年06月17日 12:17(Sunday) 
 *   描    述：
 *
 ================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <errno.h>
#include <ctype.h>

#include "wrap.h"

#define MAXLINE 80
#define SERV_PORT 33000
#define OPEN_MAX 1024

int main(int argc,char *argv[])
{
	int i,j,maxi,listenfd,connfd,sockfd;
	int nready;
	ssize_t n;

	char buf[MAXLINE],str[INET_ADDRSTRLEN];
	socklen_t clilen;
	struct pollfd client[OPEN_MAX];
	struct sockaddr_in cliaddr, servaddr, client_addr[OPEN_MAX];

	listenfd = Socket(AF_INET,SOCK_STREAM,0);

	int opt = 1;//端口复用
	setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	Listen(listenfd,128);

	client[0].fd = listenfd;
	client[0].events = POLLIN;

	for(i = 1;i<OPEN_MAX;i++)
	{
		client[i].fd = -1;
	}

	maxi = 0;

	while(1)
	{
		nready = poll(client,maxi + 1,-1);

		if(client[0].revents & POLLIN)
		{
			clilen = sizeof(cliaddr);
			connfd = Accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);
			printf("received from %s at PORT %d\n",
						inet_ntop(AF_INET,&cliaddr.sin_addr,str,sizeof(str)),
						ntohs(cliaddr.sin_port));

			for(i = 1;i<OPEN_MAX;i++)
			{
				if(client[i].fd < 0)
				{
					client_addr[i] = cliaddr;
					client[i].fd = connfd;
					printf("on set client fd %d i %d\n",connfd,i);
					break;
				}
			}

			if(i == OPEN_MAX)
			{
				perr_exit("too many clients");
			}

			client[i].events = POLLIN;

			if(i > maxi)
			{
				maxi = i;
			}

			if(--nready <= 0)
			{
				continue;
			}
		}

		for(i=1;i<=maxi;i++)
		{
			if(client[i].fd < 0)
			{
				continue;
			}
			sockfd = client[i].fd;

			if(client[i].revents & POLLIN)
			{
				n = Read(sockfd,buf,MAXLINE);
				if(n < 0)
				{
					if(errno == ECONNRESET) //收到 RST 标志 重联
					{
						printf("client[%d] aborted connection\n",i);
						Close(sockfd);
						client[i].fd = -1;
					}
					else
					{
						perr_exit("rerad error");
					}
				}
				else if(n == 0)
				{
					printf("client[%d] closed connection\n",i);
					Close(sockfd);
					client[i].fd = -1;
				}
				else
				{
					for(j=0;j<n;j++)
					{
						buf[j] = toupper(buf[j]);
					}
					printf("received from %s at PORT %d Msg:%s",
								inet_ntop(AF_INET,&client_addr[i].sin_addr,str,sizeof(str)),
								ntohs(client_addr[i].sin_port),buf);
					Writen(sockfd,buf,n);
				}
				if(--nready <=0)
				{
					break;
				}
			}
		}

	}
	return 0;
}
