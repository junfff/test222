#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
   pid_t pid;
   pid = fork();
   if(pid == -1)
   {
      perror("fork error !!");
      exit(1);
   }
   else if(pid > 0)
   {
	   sleep(6);
     printf("this is parent !!\n");
   }
   else
   {
     // int ret = execlp("ls","ls","-la",NULL);
      //int ret = execl("/bin/ls","ls","-la",NULL);
      //sleep(3);
      //int ret2 = execl("./fork_test","123",NULL);

      char *argv[]={"ls","-la",NULL};
      execv("/bin/ls",argv);
   }
   return 0;
}
