/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：client.c
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年06月29日 23:06(Friday) 
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
	struct sockaddr_in localaddr;
	int confd;
	ssize_t len;
	char buf[BUFSIZ];

	struct ip_mreqn group;

	confd = socket(AF_INET,SOCK_DGRAM,0);

	bzero(&localaddr,sizeof(localaddr));
	localaddr.sin_family = AF_INET;
	inet_pton(AF_INET,"0.0.0.0",&localaddr.sin_addr.s_addr);
	localaddr.sin_port = htons(CLIENT_PORT);

	bind(confd,(struct sockaddr *)&localaddr,sizeof(localaddr));

	inet_pton(AF_INET,GROUP,&group.imr_multiaddr); //设置 组播地址
	inet_pton(AF_INET,"0.0.0.0",&group.imr_address); //设置 本地任意ip 加入到组播 组
	group.imr_ifindex = if_nametoindex("wlx002b8f30addf"); // 设置 网卡名字

	setsockopt(confd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&group,sizeof(group)); //加入 组播组

	while(1)
	{
		len = recvfrom(confd,buf,sizeof(buf),0,NULL,0);
		write(STDOUT_FILENO,buf,len);
	}
	close(confd);

	return 0;
}
