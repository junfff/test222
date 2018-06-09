#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <netdb.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <errno.h>




ssize_t Readn(int fd,void *vptr,size_t n)
{
  size_t nleft;   //剩余未读取的字节数
	ssize_t nread;  //int实际读到的字节数
	char *ptr;

	ptr = vptr;
	nleft = n;

	while(nleft > 0)
	{
		if((nread = read(fd,ptr,nleft)) < 0)
		{
			if(errno == EINTR)
			{
				nread = 0;
			}
			else
			{
				return -1;
			}
		}
		else if(nread == 0)
		{
			break;
		}

		nleft -=nread;
		ptr +=nread;
	}

	return n - nleft;
}


ssize_t Writen(int fd,const void *vptr,size_t n)
{
	size_t nleft;
	ssize_t nwriten;
	const char *ptr;

	ptr = vptr;
	nleft = n;

	while(nleft > 0)
	{
		if((nwriten = write(fd,ptr,nleft)) <= 0)
		{
			if(nwriten < 0 && errno == EINTR)
			{
				nwriten = 0;
			}
			else
			{
				return -1;
			}

		}

		nleft -= nwriten;
		ptr += nwriten;

	}

	return n;
}


static ssize_t my_read(int fd,char *ptr)
{
	static int read_cnt;
	static char *read_ptr;
	static char read_buf[100];

	if(read_cnt <=0)
	{
		while(1)
		{
			if((read_cnt = read(fd,read_buf,sizeof(read_buf))) < 0)
			{
				if(errno == EINTR)
				{
					continue;
				}
				return -1;
			}
			else if(read_cnt == 0)
			{
				return 0;
			}

      read_ptr = read_buf;
			break;
		}
	}
	read_cnt--;
	*ptr = *read_ptr++;

	return 1;
}
// readline ------ fgets  
ssize_t Readline(int fd,void *vptr,size_t maxlen)
{
	ssize_t n,rc;
	char c, *ptr;
	ptr = vptr;

	for(n = 1;n < maxlen;n++)
	{
		if((rc = my_read(fd,&c)) == 1)
		{
			*ptr++ = c;   // ptr[] = hello\n
			if(c == '\n')
			{
				break;
			}
		}
		else if(rc == 0)
		{
			*ptr = 0;
			return n-1;
		}
		else
		{
			return -1;
		}
	}
	*ptr = 0;

	return n;
}




