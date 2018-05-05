#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
   char *val;
   const char *name = "ABD";

   val = getenv(name);
   printf("getenv name = %s val = %s\n",name,val);

   setenv(name,"haha-this-is-ABD",1);

   val = getenv(name);
   printf("getenv B name = %s val = %s\n",name,val);

   int ret = unsetenv("ABD");
   printf(" unsetenv ret is = %d \n",ret);
   
   val = getenv(name);
   printf("getenv C name = %s val = %s",name,val);


   return 0;
}
