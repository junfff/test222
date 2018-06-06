#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <netdb.h>
#include <ctype.h>
#include <arpa/inet.h>

#define SERVER_PORT 6666
#define SERVER_IP "127.0.0.1"
int main()
{
	int lfd, cfd;
	int backlog = 100;
  struct sockaddr_in addr;
	struct sockaddr_in caddr;
  char buf[BUFSIZ];



	//int socket(int domain, int type, int protocol);
  lfd = socket(AF_INET,SOCK_STREAM,0);
	if(lfd == -1)
	{
		printf("socket error !!");
		exit(1);
	}
  
//	 int bind(int sockfd, const struct sockaddr *addr,
  //              socklen_t addrlen);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	//addr.sin_addr.s_addr = htonl(INADDR_ANY);  //inet_pton(SERVER_IP);
	//int inet_pton(int af, const char *src, void *dst);
	int intip = 0;
	inet_pton(AF_INET,SERVER_IP,&intip);
	addr.sin_addr.s_addr = intip;
    
	int ret = bind(lfd,(struct sockaddr *)&addr,sizeof(addr));
	if(ret == -1)
	{
		printf("bind error !!");
		exit(1);
	}

	// int listen(int sockfd, int backlog);
	ret = listen(lfd,backlog);
	if(ret == -1)
	{
		printf("listen error !!");
		exit(1);
	}

	printf("server accept !!");
	socklen_t caddrlen = sizeof(caddr);
	//int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
	cfd = accept(lfd,(struct sockaddr *)&caddr,&caddrlen);
	if(cfd == -1)
	{
		printf("accept error !!");
		exit(1);
	}

	while(1){
	 //ssize_t read(int fd, void *buf, size_t count);
	 printf("server start read!!\n");
  ret = read(cfd,buf,sizeof(buf));
	if(ret == -1)
	{
		printf("read error !!");
		exit(1);
	}
	printf("server read ret = %d\n",ret);

	for(int i = 0;i<ret;i++)
	{
		buf[i] = toupper(buf[i]);
	}

	ret = write(cfd,buf,ret);
	if(ret == -1)
	{
		printf("write error !!");
		exit(1);
	}
	printf("server write ret = %d\n",ret);
	}
	close(lfd);
	close(cfd);

	printf("server finish !!");
   return 0;
}
