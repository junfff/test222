#include "../include/Business/PersonBusiness.h"
#include "./../include/Business/DefineProtobuf.h"
#include "../include/person.pb.h"
#include "myevents.h"
#include "string.h"
#include<iostream>

#include <uuid/uuid.h>

using namespace protobufMsg;
using namespace std;
namespace Business
{
	PersonBusiness::PersonBusiness(int id)
	{
		PersonBusiness:: id = id;
	}
    int PersonBusiness::Get_ID()
    {
    	return id;
    }
	int PersonBusiness::Process(char *buf,void *arg)
	{
		struct myevent_s *ev = (struct myevent_s *)arg;
		int size = strlen(buf);

		protobufMsg:: Person p;

    	p.ParseFromString(buf);

		cout << "write buf length = " << size << "\t";
		cout << "id = " << p.id() << "\t";
		cout << "name = " << p.name() << "\t";
		cout << "email = " << p.email() << "\t" << endl;


		p.set_email("james922@153.com");
		p.set_id(123321);
		p.set_name("junfffg");

		string str;
		p.SerializeToString(&str);

		int len = str.length();
		char data[len];
		strcpy(data,str.c_str());
		printf(">>> data is :%s,len:%d\n",data,len);

		ev->Ime->Encode(MSG_PERSON,data,ev->buf,&ev->len);


		eventset(ev,send_data,ev);
 		threadpool_add(thp,process_event,(void *)ev);


 		struct  account_info info = {0};
		char out[16];
		uuid_t uu;
		uuid_generate_random( uu );
		uuid_unparse_upper( uu, out );
		strcpy((char *)info.uuid,out);

		strcpy((char *)info.accountId,"accountId123");
		strcpy((char *)info.pwd,p.name().c_str());
		strcpy((char *)info.email,p.email().c_str());
		strcpy((char *)info.name,p.name().c_str());
		strcpy((char *)info.mobilephone,"15710667093");
		info.sex = 1;

 		int ret = sql_insert(&info);

 		printf("sql_insert ret = %d !!!\n",ret );
		return 0;
	}

}
