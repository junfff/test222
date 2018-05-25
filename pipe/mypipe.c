#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
       #include <sys/stat.h>
       #include <fcntl.h>



void OnChild(int sig)
{
   pid_t pid =0;
	 int status = 0;
	 while((pid = waitpid(0,&status,WNOHANG)) > 0)
	 {
	     printf("OnChild !!------------------------\n");
			 if(WIFEXITED(status))
			 {
			    printf("child exit with %d\n",WEXITSTATUS(status));
			 }
			 else if(WIFSIGNALED(status))
			 {
			    printf("child signal %d\n",WTERMSIG(status));
			 }
	 }


}

int main()
{
	//mkfifo();
        //char mybuf[1024];
        //int fdd = open("mp",O_WRONLY);
        //int a = read(fdd,mybuf,sizeof(mybuf));

        //printf("mkfifo finish !! a = %d\n",a);

        //return 0;

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
		sleep(2);
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

		signal(SIGCHLD,OnChild);
           close(fd[0]);
	   sleep(5);
	   //父进程写
	   char *pbuf= "parent say holle !!!\n";
	   write(fd[1],pbuf,strlen(pbuf));
           printf("praent finish !!!\n");


while(1)
{
  sleep(1);
   printf("parent waiting child,,,,,,,\n");
}
	}
	return 0;
}
