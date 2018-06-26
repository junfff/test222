/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：client.c
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年06月26日 23:35(Tuesday) 
 *   描    述：
 *
 ================================================================*/

#include <stdio.h>
//#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <string.h>

#define SERV_PORT 33000

int main()
{
	struct sockaddr_in servaddr;
	int sockfd,n;
	char buf[BUFSIZ];

	sockfd = socket(AF_INET,SOCK_DGRAM,0);

	bzero(&servaddr,sizeof(servaddr));
	inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);

	while(fgets(buf,BUFSIZ,stdin) != NULL)
	{
		n = sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
		if(n == -1)
		{
			perror("sendto error");
		}

		n = recvfrom(sockfd,buf,BUFSIZ,0,NULL,0);
		if(n == -1)
		{
			perror("recvfrom error");
		}

		write(STDOUT_FILENO,buf,n);
	}
	close(sockfd);

	return 0;
}
