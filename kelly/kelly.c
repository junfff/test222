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

//2.40	2.90	3.50	39.79%	32.93%	27.28%	0.95	0.97 | 0.90 | 1.01 60 20 19

int main()
{
	float p1,p2,p3,s1,s2,s3,fh,k1,k2,k3,b1,b2,b3;
    float bk1,bk2,bk3,pk1,pk2,pk3;

	p1=2.4;
	p2=2.9;
	p3=3.5;
	s1=39.79;
	s2=32.93;
	s3=27.28;
	fh=95;
	k1=0.97;
	k2=0.9;
	k3=1.01;
	b1=60;
	b2=20;
	b3=19;


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
	return 0;
}
