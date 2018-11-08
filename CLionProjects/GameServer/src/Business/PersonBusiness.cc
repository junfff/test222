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


		return 0;
	}

}
