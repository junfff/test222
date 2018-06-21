/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：server_pthread.c
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年06月09日 22:05(Saturday) 
 *   描    述：
 *
 ================================================================*/
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <ctype.h>
#include <fcntl.h>

#include "./include/wrap.h"
#include "./include/person.pb.h"
namespace protobuf = google::protobuf;
using namespace protobufMsg;
using namespace std;

#define SERVER_PORT 33000
#define BACK_LOG 128
struct s_info
{
	struct sockaddr_in addr;
	int fd;
};
void *OnClientLink(void *arg)
{
	int n;
	//int i;
	struct s_info *info = (struct s_info *)arg;
	char buf[BUFSIZ];
	char str[BUFSIZ];

	while(1)
	{
    	//ssize_t read(int fd, void *buf, size_t count);
		n = Read(info->fd,buf,BUFSIZ);
		if(n == 0)
		{
			printf("the client %d closed ...\n",info->fd);
			break;
		}

      	printf("received from %s at PORT %d\n",
        			inet_ntop(AF_INET,&info->addr.sin_addr.s_addr,str,sizeof(str)),
        			ntohs(info->addr.sin_port));

      	//	for(i = 0; i < n; i++)
      	//	{
        //	buf[i] = toupper(buf[i]);
      	//}
		protobufMsg:: Person p;

      	p.ParseFromString(buf);

		cout << "write buf length = " << n << "\t";
		cout << "id = " << p.id() << "\t";
		cout << "name = " << p.name() << "\t";
		cout << "email = " << p.email() << "\t" << endl;

		p.set_id(p.id() + 100);

		//Write(STDOUT_FILENO,buf,n);

		string newstr = p.SerializeAsString();

		Write(info->fd,newstr.c_str(),newstr.length());

		cout << "send msg " << newstr.c_str() << "length: " << newstr.length()  << endl;

	}
	//int close(int fd);
	Close(info->fd);
   	printf("client closed  from %s at PORT %d\n",
        		inet_ntop(AF_INET,&(*info).addr.sin_addr,str,sizeof(str)),
        		ntohs((*info).addr.sin_port));

	return (void *)0;
}
int main()
{
	printf("server start!!");

	struct s_info info;
	struct s_info clie[256];
	int i = 0;

   	//int socket(int domain, int type, int protocol);
	info.fd = Socket(AF_INET,SOCK_STREAM,0);

	int opt = 1;
	setsockopt(info.fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

	info.addr.sin_family = AF_INET;
	info.addr.sin_port = htons(SERVER_PORT);
   	info.addr.sin_addr.s_addr = htonl(INADDR_ANY);

	//int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	Bind(info.fd,(struct sockaddr *)&info.addr,sizeof(info.addr));

	//int listen(int sockfd, int backlog);
	Listen(info.fd,BACK_LOG);
	printf("wait for client connect...\n");

	socklen_t addrlen;
	struct sockaddr_in caddr;
	while(1)
	{
		addrlen = sizeof(caddr);
		//int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
		int cfd = Accept(info.fd,(struct sockaddr *)&caddr,&addrlen);
		clie[i].fd = cfd;
		clie[i].addr = caddr;

      	//int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
      	//                 void *(*start_routine) (void *), void *arg);

		pthread_t tid;
		pthread_create(&tid,NULL,OnClientLink,(void *)&clie[i]);
		// int pthread_detach(pthread_t thread);
		pthread_detach(tid);
		i++;
		char str[BUFSIZ];
      	printf("accept from %s at PORT %d\n",
        			inet_ntop(AF_INET,&caddr.sin_addr.s_addr,str,sizeof(str)),
        			ntohs(caddr.sin_port));
	}
	return 0;
}
