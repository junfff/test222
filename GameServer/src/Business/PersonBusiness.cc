#include "../include/Business/PersonBusiness.h"
#include "../include/person.pb.h"
#include "myevents.h"
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

		eventset(ev,send_data,ev);
 		threadpool_add(thp,process_event,(void *)ev);
		return 0;
	}

}
