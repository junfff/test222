#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <netdb.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <errno.h>
#include "wrap.h"

void perr_exit(const char *s)
{
	perror(s);
	exit(-1);
}

int Accept(int fd, struct sockaddr *addr, socklen_t *addrlen)
{
	int n;

	while(1)
	{
		if((n = accept(fd,addr,addrlen)) < 0)
		{
			if((errno == ECONNABORTED) || (errno == EINTR))
			{
				continue;
			}
			else
			{
				perr_exit("accept error");
			}
		}
		return n;
	}
}

int Bind(int fd,const struct sockaddr *addr,socklen_t addrlen)
{
	int n;

	if((n = bind(fd,addr,addrlen)) < 0)
	{
		perr_exit("bind error");
	}
	return n;
}

int Connect(int fd,const struct sockaddr *addr,socklen_t addrlen)
{
	int n;
	printf("-----------------in wrap before connect()\n");
	n = connect(fd,addr,addrlen);
	printf("-----------------in wrap connect() return %d\n",n);
	if(n < 0)
	{
		perr_exit("connect error");
	}

	return n;
}

int Listen(int fd,int backlog)
{
	int n;

	if((n = listen(fd,backlog)) < 0)
	{
		perr_exit("listen error");
	}

	return n;
}

int Socket(int family,int type,int protocol)
{
	int n;

	if((n = socket(family,type,protocol)) < 0)
	{
		perr_exit("socket error");
	}
	return n;
}

ssize_t Read(int fd,void *ptr,size_t nbytes)
{
	ssize_t n;

	while(1)
	{
		if((n = read(fd,ptr,nbytes)) == -1)
		{
			if(errno == EINTR)
			{
				continue;
			}
			else
			{
				return -1;
			}
		}

		return n;
	}
}

ssize_t Write(int fd,const void *ptr,size_t nbytes)
{
	ssize_t n;

	while(1)
	{
		if((n = write(fd,ptr,nbytes)) ==  -1)
		{
			if(errno == EINTR)
			{
				continue;
			}
			else
			{
				return -1;
			}
		}

		return n;
	}
}

int Close(int fd)
{
	int n;
	if((n = close(fd)) == -1)
	{
		perr_exit("close error");
	}

	return n;
}


ssize_t Readn(int fd,void *vptr,size_t n)
{
  size_t nleft;   //剩余未读取的字节数
  ssize_t nread;  //int实际读到的字节数
	char *ptr;

	ptr = (char *)vptr;
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

	ptr = (char *)vptr;
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


ssize_t my_read(int fd,char *ptr)
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
	ptr = (char *)vptr;

	for(n = 1;n < (int)maxlen;n++)
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




