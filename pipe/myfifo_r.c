#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
     int fd = open("myff",O_RDONLY);
     if(fd == -1)
     {
	perror("open error !!\n");
	exit(1);
     } 
	printf("open fifo succeed !\n");
	
	char buf[1024];
	int ret = read(fd,buf,sizeof(buf));
	if(ret > 0)
	{
	   printf("read %d, buf is  %s  !!!\n",ret,buf);
	}
	printf("read finish !!!\n");
	return 0;
}

