#include <stdio.h>
#include <cale.h>
#include <tools.h>

int nGlobalVar = 0;

int tempFunction(int a, int b)
{
    printf("tempFunction is called, a = %d, b = %d /n", a, b);
    return (a + b);
}

int ttmain()
{
    int n;
    n = 1;
    n++;
    n--;

    nGlobalVar += 100;
    nGlobalVar -= 12;

    printf("n = %d, nGlobalVar = %d /n", n, nGlobalVar);

    n = tempFunction(1, 2);
    printf("n = %d", n);

    return 0;
}

int main()
{
   int ret = Add(100,50);
   printf("ret is = %d",ret);
   ttmain();  
   ret = tempFunction(200,300);
   
   int last = 0;
   for(int i = 0;i < 200;i++)
   {
     
	ret += tempFunction(last,i);
	last = i;

      printf("for -- ret = %d , last = %d , i = %d . /n",ret,last,i);

   }
	ret = TAdd(ret,last);
	Show(ret);
	Show(last);
	SayHello();
	
   return 0;
}
