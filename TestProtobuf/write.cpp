/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：Write.cpp
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年06月16日 21:18(Saturday) 
 *   描    述：
 *
 ================================================================*/
#include "example.pb.h"

#include <stdio.h>
#include <fstream>
#include <iostream>
using namespace std;
//using namespace ptest;

int main()
{
	cout << "this is c++" << endl;
	cout << "hello" << endl;

	ptest::person p;
	p.set_name("liujunfeng");
	p.set_id(110);
	p.set_email("67449789@163.com");

	fstream output("out.log",ios::out | ios::trunc | ios::binary);
	if(!p.SerializeToOstream(&output))
	{
		cerr << "Failed to Write msg" << endl;
		return -1;
	}


	return 0;

}
