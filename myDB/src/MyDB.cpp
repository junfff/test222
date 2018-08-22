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


MyDB::~MyDB()
{
	if(connection != NULL)   //关闭数据库 连接
	{
		mysql_close(connection);
	}
}

bool MyDB::initDB(string host,string user,string pwd,string db_name)
{
	//函数mysql_real_connect 建立一个数据库连接
	// 成功返回MYSQL* 连接句柄，失败返回NULL
	connection = mysql_real_connect(connection,host.c_str(),
				user.c_str(),pwd.c_str(),db_name.c_str(),0,NULL,0);
	if(connection == NULL)
	{
		cout << "Error:" << mysql_error(connection);
		exit(1);
	}
	return true;
}


bool MyDB::exeSQL(string sql)
{
	// mysql_query() 执行成功返回 0 失败返回非0
	if(mysql_query(connection,sql.c_str()))
	{
		cout << "Query Error:" << mysql_error(connection);
		exit(1);
	}
	else
	{
		result = mysql_use_result(connection); // 获取结果集
		//mysql_field_count() 返回connection 查询的列数
		for(int i=0;i<mysql_field_count(connection);++i)
		{
			//获取下一行
			row = mysql_fetch_row(result);
			if(row <= 0)
			{
				break;
			}
			// mysql_num_fields() 返回结果集中的子段数
			for(int j=0;j<mysql_num_fields(result);++j)
			{
				cout << row[j] << " ";
			}
			cout << endl;
		}
		//释放结果集的内存
		mysql_free_result(result);
	}
	return true;
}
