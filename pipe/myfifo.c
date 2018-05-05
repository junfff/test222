#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 #include <sys/types.h>
       #include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	int fd;	
//建立管道：
	int ret;
	if(access("myff",F_OK) == -1)
	{
	ret = mkfifo("myff",0777);
	if(ret == -1)
	{
	   perror("mkfifo error !!!\n");
	   exit(1);
	}
	}
//打开管道：
	fd = open("myff", O_WRONLY);
	if(fd == -1)
	{
	   perror("open error !!!");
	   exit(1);
	}
//写数据：
	char *buf= "this is my fifo !!!\n";
	write(fd,buf,strlen(buf));

	printf("write finish !!!!\n ");
	return 0;
}
