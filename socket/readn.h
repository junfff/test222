#ifndef _READ_HELPER_H_
#define _READ_HELPER_H_

ssize_t Readn(int fd,void *vptr,size_t n);
ssize_t Writen(int fd,const void *vptr,size_t n);
static ssize_t my_read(int fd,char *ptr);
ssize_t Readline(int fd,void *vptr,size_t maxlen);

#endif
