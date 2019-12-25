#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
   int fd;
   fd = open("out.txt",O_WRONLY | O_CREAT | O_TRUNC,0644);
   if(fd < 0)
   {
      perror("open error !!");
      exit(1);
   }

   dup2(fd,STDOUT_FILENO);
   printf("start execlp ps !!");
   execlp("ps","ps","aux",NULL);
   printf("这句话是执行 不到的！ 哈哈哈哈哈哈哈哈 ！！！");
   close(fd);
   return 0;
}
