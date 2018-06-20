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

typedef struct odds
{
    char  name[256];
	float fs[100];
}odds;
void str_replace(char * cp, int n,const  char * str)
{
    int lenofstr;
    //int i;
    char * tmp;
    lenofstr = strlen(str);
    //str3比str2短，往前移动
    if(lenofstr < n)
    {
        tmp = cp+n;
        while(*tmp)
        {
            *(tmp-(n-lenofstr)) = *tmp; //n-lenofstr是移动的距离
            tmp++;
        }
        *(tmp-(n-lenofstr)) = *tmp; //move '\0'
    }
    else
      //str3比str2长，往后移动
      if(lenofstr > n)
      {
          tmp = cp;
          while(*tmp) tmp++;
          while(tmp>=cp+n)
          {
              *(tmp+(lenofstr-n)) = *tmp;
              tmp--;
          }
      }
    strncpy(cp,str,lenofstr);
}
int replace(char *token,const char *from,const char *to)
{
	int count = 0;
	//开始查找字符串str2
    char *p = strstr(token,from);
    while(p)
    {
        count++;
        //每找到一个str2，就用str3来替换
        str_replace(p,strlen(from),to);
        p = p+strlen(to);
        p = strstr(p,from);
    }
    printf("replace count  = %d from=(%s),to=(%s)\n",count,from,to);
	return count;
}
int Parse(char *buf,odds *od)
{
	int index = 0;
	//char *tmp = buf;
	//char *ptr = NULL;
	float result;

	char *saveptr;

	char* token = strtok_r(buf, " ",&saveptr);
    while( token != NULL )
    {
		if(index == 0)
		{
			strcpy(od->name,token);
			//printf("=== od name = %s\n",token);
		}
		else
		{
        	result = atof(token);
       		od->fs[index - 1] = result;
        	//printf( "(%s) === result:%g\n", token,result );
		}
    	index++;
        token = strtok_r( NULL, " ",&saveptr);
    }

	printf("======================================\n");
	return 0;
}
void Show(odds *od)
{
	float c1,c2,c3,p1,p2,p3,s1,s2,s3,fh,k1,k2,k3,b1,b2,b3;
    float bk1,bk2,bk3,pk1,pk2,pk3;
    c1 = od->fs[0];
    c2 = od->fs[1];
    c3 = od->fs[2];
    p1 = od->fs[3];
    p2 = od->fs[4];
    p3 = od->fs[5];
    s1 = od->fs[6];
    s2 = od->fs[7];
    s3 = od->fs[8];
    fh = od->fs[9];
    k1 = od->fs[10];
    k2 = od->fs[11];
    k3 = od->fs[12];
    b1 = od->fs[13];
    b2 = od->fs[14];
    b3 = od->fs[15];

	fh *= 100;

	printf(">>>>>>>>>>  %s: %g\t%g\t%g\t%g\t%g\t%g\t <<<<<<<<<<<<<<<<<<<\n}",od->name,c1,c2,c3,p1,p2,p3);
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
	odds od;
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

    const char *tostr = " ";
    const char *fstr1 = "	";
    const char *fstr2 = "|";
    while( token != NULL )
    {
    	replace(token,fstr1,tostr);
    	replace(token,fstr2,tostr);



    	Parse(token,&od);
    	Show(&od);
        token = strtok_r( NULL, "\n",&saveptr);
    }


	return 0;
}
