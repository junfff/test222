/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：reader.cpp
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年06月17日 00:31(Sunday) 
 *   描    述：
 *
 ================================================================*/

#include "example.pb.h"
#include <fstream>
#include <iostream>
using namespace std;

void showMsg(const ptest::person p)
{
	cout << p.name() << endl;
	cout << p.id() << endl;
	cout << p.email() << endl;
}

int main()
{
	ptest::person p;
	fstream input("out.log",ios::in | ios::binary);
	if(!p.ParseFromIstream(&input))
	{
		cerr << "Failed to read file" << endl;
		return -1;
	}
	showMsg(p);

	return 0;
}
