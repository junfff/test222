/*************************************************************************
 *     > File Name: MyDB.cpp
 *         > Author: SongLee
 *             > E-mail: lisong.shine@qq.com
 *                 > Created Time: 2014年05月04日 星期日 23时37分08秒
 *                     > Personal Blog: http://songlee24.github.io
 *                      ************************************************************************/
#include "MyDB.h"
#include <cstdlib>
#include <iostream>
using namespace std;

MyDB::MyDB()
{
	connection = mysql_init(NULL);  //初始化数据库连接变量
    if (connection == NULL) {
		cout << "Error:" << mysql_error(connection);
		exit(1);
	}

}

