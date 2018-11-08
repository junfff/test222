//
// Created by ljf on 11/8/18.
//

#include "../include/Business/RegisterBusiness.h"
#include "./../include/Business/DefineProtobuf.h"
#include "../include/register.pb.h"
#include "myevents.h"
#include "string.h"
#include<iostream>
#include <uuid/uuid.h>
#include <register.pb.h>
#include "../include/sqlop.h"


using namespace protobufMsg;
using namespace std;
namespace Business
{
    RegisterBusiness::RegisterBusiness(int id)
    {
        RegisterBusiness:: id = id;
    }
    int RegisterBusiness::Get_ID()
    {
        return id;
    }
    int RegisterBusiness::Process(char *buf,void *arg)
    {
        struct myevent_s *ev = (struct myevent_s *)arg;
        int size = strlen(buf);

        protobufMsg:: Register_CS msg;

        msg.ParseFromString(buf);

        cout << "write buf length = " << size << "\t";
        cout << "id = " << msg.accountid() << "\t";
        cout << "name = " << msg.name() << "\t";
        cout << "email = " << msg.email() << "\t" << endl;




        struct  account_info info = {0};
        char out[16];
        uuid_t uu;
        uuid_generate_random( uu );
        uuid_unparse_upper( uu, out );
        strcpy((char *)info.uuid,out);

        strcpy(info.accountId,msg.accountid().c_str());
        strcpy(info.pwd,msg.pwd().c_str());
        strcpy(info.email,msg.email().c_str());
        strcpy(info.name,msg.name().c_str());
        strcpy(info.mobilephone,msg.mobilephone().c_str());
        info.sex = (short)msg.sex();

        int ret = sql_insert(&info);

        printf("sql_insert ret = %d !!!\n",ret );


        //result success = 0  fail = 1 systemError = 2 paramError = 3
        protobufMsg:: Register_SC responseMsg;
        responseMsg.set_code(ret);
        string str;
        responseMsg.SerializeToString(&str);
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
