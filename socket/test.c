/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：test.cpp
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年06月12日 00:01(Tuesday) 
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

struct s_info
{
   struct sockaddr_in addr;
   int fd;
};

int main()
{
	struct sockaddr_in caddr;
	//cout << "hello" << endl;
	printf("dddd");
	struct s_info info;
	info.addr = caddr;

   int fd;
   char buf[BUFSIZ];
	Read();



   struct sockaddr addr;
   addr.sa_family = AF_INET;




	return 0;
}
