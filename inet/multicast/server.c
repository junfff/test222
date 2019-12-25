/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：server.c
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年06月29日 18:26(Friday) 
 *   描    述：
 *
 ================================================================*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <net/if.h>

#define SERV_PORT 33000
#define CLIENT_PORT 33001
#define MAXLINE 1500

#define GROUP "239.0.0.2"

int main()
{
	int sockfd;
	struct sockaddr_in serveraddr, clientaddr;
	char buf[MAXLINE] = "itcast\n";
	struct ip_mreqn group;

	sockfd = socket(AF_INET,SOCK_DGRAM,0);

	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERV_PORT);

	bind(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));

	inet_pton(AF_INET,GROUP,&group.imr_multiaddr);// 设置组地址
	inet_pton(AF_INET,"0.0.0.0",&group.imr_address);// 本地任意ip
	group.imr_ifindex = if_nametoindex("wlx002b8f30addf");// 给出网卡名字 eth0

	setsockopt(sockfd,IPPROTO_IP,IP_MULTICAST_IF,&group,sizeof(group));//组播权限

	bzero(&clientaddr,sizeof(clientaddr));
	clientaddr.sin_family = AF_INET;
	inet_pton(AF_INET,GROUP,&clientaddr.sin_addr.s_addr);  // ipv4 239.0.0.2+9000
	clientaddr.sin_port = htons(CLIENT_PORT);

	int i = 0;
	while(1)
	{
		sprintf(buf,"itcast %d\n",i++);
		sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&clientaddr,sizeof(clientaddr));
		sleep(1);
	}
	close(sockfd);

	return 0;
}

