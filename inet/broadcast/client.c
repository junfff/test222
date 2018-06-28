/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：client.c
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年06月28日 22:39(Thursday) 
 *   描    述：
 *
 ================================================================*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <net/if.h>

#define SERV_PORT 33000
#define CLIENT_PORT 33001
#define MAXLINE 1500

#define BROADCAST_IP "192.168.14.255"

int main()
{
	struct sockaddr_in localaddr;
	int confd;
	ssize_t len;
	char buf[MAXLINE];

	confd = socket(AF_INET,SOCK_DGRAM,0);

	bzero(&localaddr,sizeof(localaddr));
	localaddr.sin_family = AF_INET;
	inet_pton(AF_INET,"0.0.0.0",&localaddr.sin_addr.s_addr);
	localaddr.sin_port = htons(CLIENT_PORT);

	int ret = bind(confd,(struct sockaddr *)&localaddr,sizeof(localaddr));
	if(ret == 0)
	{
		printf("...bind ok...\n");
	}

	while(1)
	{
		len = recvfrom(confd,buf,sizeof(buf),0,NULL,0);
		write(STDOUT_FILENO,buf,len);
	}

	close(confd);
	return 0;
}
