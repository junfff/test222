/*************************************************************************
 *     > File Name: MyDB.h
 *         > Author: SongLee
 *             > E-mail: lisong.shine@qq.com
 *                 > Created Time: 2014年05月04日 星期日 23时25分50秒
 *                     > Personal Blog: http://songlee24.github.io
 *                      ************************************************************************/
#ifndef __MYBD_H__
#include <mysql/mysql.h>
#include <iostream>
#include <string>
using namespace std;

class MyDB {
    public:
		MyDB();
		~MyDB();
		bool initDB(string host, string user, string pwd, string db_name);
		bool exeSQL(string sql);

    private:
		MYSQL *connection;
		MYSQL_RES *result;
		MYSQL_ROW row;
};

#endif
