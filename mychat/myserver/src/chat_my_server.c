 #include <sys/types.h>
       #include <unistd.h>



void CreatorFifo()
{
   fork();

}
char* ReadFifo()
{
   char *buf = "test";
   return buf;
}

