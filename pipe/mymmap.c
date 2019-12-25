#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

int main()
{
	//int fd = open("mmap.txt",O_RDONLY);
	int fd = open("mmap.txt",O_RDWR);
	if(fd < 0)
	{
	   perror("open error !");
	   exit(1);
	}
	int len = 4;
	int ret = ftruncate(fd,len);
	 //lseek(fd, 0, SEEK_SET);
	if(ret < 0)
	{
	   perror("ftruncate error !! \n");
	   exit(1);
	}
	//int fdsize = lseek(fd,0,SEEK_END);
   //void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
   char *addr = NULL;
   addr = mmap(NULL,len,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
	if(addr == MAP_FAILED)
	{
	   perror("mmap error !!!!");
	   exit(1);
	}
	
	strcpy(addr,"abc");
	close(fd);
	printf("see see len is %d \n",len);
	ret = munmap(addr,len);
	if(ret == -1)
	{
	   perror("munmap error !!");
	   exit(1);
	}
	return 0;
}
