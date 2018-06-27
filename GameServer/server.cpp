/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：server.cpp
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年06月27日 16:34(Wednesday) 
 *   描    述：
 *
 ================================================================*/
#include "./include/eventepoll.h"
#include "./include/threadpool.h"
#include <string.h>
#include <stdio.h>
int main(int argc,char *argv[])
{
	//threadpool_t *thp = threadpool_create(3,100,100); // 创建 线程  最小线程，最大，队列最大
	//printf("pool inited\n");

	//printf("add task %d\n",i);
	//threadpool_add(thp,process,(void *)&num[i]);


    //Epoll_Start(argc,argv,thp);

	//printf("server end >>>>>>>>>>>>\n");
	//threadpool_destroy(thp);
	Start();
	return 0;
}
