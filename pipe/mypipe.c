#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main()
{
	//mkfifo();
        char mybuf[1024];
        int fdd = open("mp",O_WRONLY);
        int a = read(fdd,mybuf,sizeof(mybuf));

        printf("mkfifo finish !! a = %d\n",a);

        return 0;

	int fd[2];
	int ret = pipe(fd);
	if(ret == -1)
	{
           perror("pipe error !!!");
	   exit(1);
	}

	pid_t pid = fork();
	if(pid == -1)
	{
           perror("fork error !!!");
	   exit(1);
	}
	else if(pid == 0)
	{
           //子进程
	  close(fd[1]);   
	  char buf[1024];
	ret =  read(fd[0],buf,sizeof(buf));
         if(ret == 0)
	 {
            printf("read end !!!\n");
	 }
         printf("on child write! \n");
	 write(STDOUT_FILENO,buf,ret);
	 printf("child finish !!!\n");
	}
	else
	{
           close(fd[0]);
	   sleep(5);
	   //父进程写
	   char *pbuf= "parent say holle !!!\n";
	   write(fd[1],pbuf,strlen(pbuf));
           printf("praent finish !!!\n");
	}
	return 0;
}
