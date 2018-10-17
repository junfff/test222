#include "../include/Business/HeartBeatBusiness.h"
#include "./../include/Business/DefineProtobuf.h"
#include "../include/HeartBeat.pb.h"
#include "myevents.h"
#include "string.h"
#include<iostream>
using namespace protobufMsg;
using namespace std;
namespace Business
{
	HeartBeatBusiness::HeartBeatBusiness(int id)
	{
		HeartBeatBusiness:: id = id;
	}
    int HeartBeatBusiness::Get_ID()
    {
    	return id;
    }
	int HeartBeatBusiness::Process(char *buf,void *arg)
	{
		struct myevent_s *ev = (struct myevent_s *)arg;
		int size = strlen(buf);

		protobufMsg:: HeartBeat p;

    	p.ParseFromString(buf);

		cout << "write buf length = " << size << "\t";
		cout << "HeartBeat id = " << p.actionid() << "\t \n";

		ev->Ime->Encode(MSG_HEARTBEAT,buf,ev->buf,&ev->len);

		eventset(ev,send_data,ev);
 		threadpool_add(thp,process_event,(void *)ev);
		return 0;
	}

}
