/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：kelly.c
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年06月19日 22:20(Tuesday) 
 *   描    述：
 *
 ================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


//       int open(const char *pathname, int flags);

//2.40	2.90	3.50	39.79%	32.93%	27.28%	0.95	0.97 | 0.90 | 1.01 60 20 19

enum dataType
{
	p1,
	p2
};
int Parse(char *buf,float fs[])
{
	int index = 0;
	//char *tmp = buf;
	//char *ptr = NULL;
	float result;

	char *saveptr;

	char* token = strtok_r(buf, " ",&saveptr);
    while( token != NULL )
    {
        result = atof(token);
        //printf( "(%s) === result:%g\n", token,result );

        fs[index] = result;
    	index++;
        token = strtok_r( NULL, " ",&saveptr);
    }

	printf("======================================\n");
	return 0;
}
void Show(float fs[])
{
	float p1,p2,p3,s1,s2,s3,fh,k1,k2,k3,b1,b2,b3;
    float bk1,bk2,bk3,pk1,pk2,pk3;
    p1 = fs[0];
    p2 = fs[1];
    p3 = fs[2];
    s1 = fs[3];
    s2 = fs[4];
    s3 = fs[5];
    fh = fs[6];
    k1 = fs[7];
    k2 = fs[8];
    k3 = fs[9];
    b1 = fs[10];
    b2 = fs[11];
    b3 = fs[12];

	fh *= 100;

	printf(">>>>>>>>>> p1 = %g\n}",p1);
	pk1 = p1*b1/100;
	pk2 = p2*b2/100;
	pk3 = p3*b3/100;

	bk1 = fh/s1*b1/100;
	bk2 = fh/s2*b2/100;
	bk3 = fh/s3*b3/100;

    printf("kelly 主胜差异：k1:   %g   ===    %g   ===   %g\n",k1,bk1,((k1+bk1)/2)-k1);
    printf("kelly 平局差异：k1:   %g   ===    %g   ===   %g\n",k2,bk2,((k2+bk2)/2)-k2);
    printf("kelly 客胜差异：k1:   %g   ===    %g   ===   %g\n",k3,bk3,((k3+bk3)/2)-k3);
    printf("pk1:%g   ,pk2:%g   ,pk3:%g\n",pk1,pk2,pk3);
}
int main()
{
	float fs[100];
	int fd;
	fd =open("/home/ljf/learn/kelly/bin/data.txt",O_RDONLY);
	if(fd == -1)
	{
		perror("open data txt error");
		exit(1);
	}

   	char buf[BUFSIZ];
	//ssize_t read(int fd, void *buf, size_t count);
    int n = read(fd,buf,sizeof(buf));
    if(n == -1)
    {
    	perror("read error");
    	exit(1);
    }
    printf("read:\n%s\n",buf);
	char *saveptr;
	char* token = strtok_r(buf, "\n",&saveptr);
    while( token != NULL )
    {
    	Parse(token,fs);
    	Show(fs);
        token = strtok_r( NULL, "\n",&saveptr);
    }


	return 0;
}
