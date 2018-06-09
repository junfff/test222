#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <netdb.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <string.h>

#define SERVER_PORT 33000
#define SERVER_IP "47.106.123.211"
//#define SERVER_IP "127.0.0.1"
int main()
{
	int lfd,ret;
	int backlog = 100;
  struct sockaddr_in addr;
  char buf[BUFSIZ];

	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	//addr.sin_addr.s_addr = htonl(INADDR_ANY);  //inet_pton(SERVER_IP);
	//addr.sin_addr.s_addr = inet_pton(SERVER_IP);
  int intip = 0;
	inet_pton(AF_INET,SERVER_IP,&intip);
	addr.sin_addr.s_addr = intip;

	//int socket(int domain, int type, int protocol);
  lfd = socket(AF_INET,SOCK_STREAM,0);
	if(lfd == -1)
	{
		printf("socket error !!");
		exit(1);
	}
  


	printf("client connect !!lfd = %d\n",lfd);
	socklen_t addrlen = sizeof(addr);
	//int connect(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
	ret = connect(lfd,(struct sockaddr *)&addr,addrlen);
	if(ret == -1)
	{
		perror(">>> connect error:");
		printf("client connect error !!ret = %s\n",strerror(ret));
		exit(1);
	}
	while(1)
	{
		printf("client start send char !!!ret = %d lfd = %d\n",ret,lfd);

		fgets(buf,sizeof(buf),stdin);
	ret = write(lfd,buf,strlen(buf));
	if(ret == -1)
	{
		printf("write error !!");
		exit(1);
	}
	printf("client send ret = %d\n}",ret);

	 //ssize_t read(int fd, void *buf, size_t count);
  ret = read(lfd,buf,sizeof(buf));
	if(ret == -1)
	{
		printf("read error !!");
		exit(1);
	}

	 printf("client rev buf is:%s\n",buf);

	 sleep(1);
	}
	close(lfd);

	printf("client finish !!");
   return 0;
}
