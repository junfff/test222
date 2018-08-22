/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：main.cpp
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年08月22日 11:20(Wednesday) 
 *   描    述：
 *
 ================================================================*/


#include<iostream>
#include "./include/MyDB.h"
using namespace std;

int main()
{
	MyDB db;
	db.initDB("localhost", "root", "songlee", "student");
	db.exeSQL("select * from student_info");
	return 0;
}
