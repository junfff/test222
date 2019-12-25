/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：server.c
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年06月30日 19:32(Saturday) 
 *   描    述：
 *
 ================================================================*/

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <stddef.h>

#include "wrap.h"

#define SERV_ADDR "serv.socket"

int main()
{
	int lfd,cfd,len,size,i;
	struct sockaddr_un servaddr,cliaddr;
	char buf[4096];

	lfd = Socket(AF_UNIX,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sun_family = AF_UNIX;
	strcpy(servaddr.sun_path,SERV_ADDR);

	//函数宏实现   定义                 实现
	//#define offsetof(type,member) ((int)&((type *)0)->MEMBER)
	len = offsetof(struct sockaddr_un,sun_path) + strlen(servaddr.sun_path);

	unlink(SERV_ADDR);
	// bind 函数 会创建 文件 
	Bind(lfd,(struct sockaddr *)&servaddr,len);

	Listen(lfd,20);

	printf("Accept ...\n");

	while(1)
	{
		len = sizeof(cliaddr);
		cfd = Accept(lfd,(struct sockaddr *)&cliaddr,(socklen_t *)&len);

		len -= offsetof(struct sockaddr_un,sun_path);
		cliaddr.sun_path[len] = '\0';

		printf("client bind filename %s\n",cliaddr.sun_path);

		while((size = read(cfd,buf,sizeof(buf))) > 0)
		{
			for(i=0;i<size;i++)
			{
				buf[i] = toupper(buf[i]);
			}
			write(cfd,buf,size);
		}
		close(cfd);

	}
	return 0;
}
