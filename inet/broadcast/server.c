/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：server.c
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年06月28日 22:17(Thursday) 
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

#define BROADCAST_IP "192.168.1.255"

int main()
{
	int sockfd;
	struct sockaddr_in serveraddr,clientaddr;
	char buf[MAXLINE];

	sockfd = socket(AF_INET,SOCK_DGRAM,0);

	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERV_PORT);

	bind(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));

	int flag = 1;
	//给 sock 赋予 广播权限
	setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&flag,sizeof(flag));

	// 构造 客户端 ip 端口 
	bzero(&clientaddr,sizeof(clientaddr));
	clientaddr.sin_family = AF_INET;
	inet_pton(AF_INET,BROADCAST_IP,&clientaddr.sin_addr.s_addr);
	clientaddr.sin_port = htons(CLIENT_PORT);

	int i = 0;
	while(1)
	{
		int id = if_nametoindex("wlx002b8f30addf");
		sprintf(buf,"Drink %d glasses of water--- id:%d\n",i++,id);
		sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&clientaddr,sizeof(clientaddr));
		sleep(1);
	}
	close(sockfd);

	return 0;
}
