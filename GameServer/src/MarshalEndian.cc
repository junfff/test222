/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：MarshalEndian.c
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年06月22日 17:58(Friday) 
 *   描    述：
 *
 ================================================================*/
#include <Interface.h>
#include "MarshalEndian.h"
#include "../include/BaseMessage.h"
#include "string.h"
#include <fstream>
#include <assert.h>
#include "../include/person.pb.h"
#include "../include/Business/BusinessMoudle.h"
#include "../include/Base/MoudlesCollection.h"

using namespace protobufMsg;
using namespace std;
// 消息解析器  

void MarshalEndian::Initialize()
{
    //_LBuff = new list<char>(2);
    list<char> _LBuff(2);
    //utf8 = new UTF8Encoding();
}

void MarshalEndian:: Dispose()
{
	MarshalEndian:: Dispose(true);
    //GC.SuppressFinalize(this);
}

void MarshalEndian:: Dispose(bool flag1)
{
    if (flag1)
    {
       	// IDisposable disposable2 = this.utf8 as IDisposable;
       	// if (disposable2 != null) { disposable2.Dispose(); }
       	// IDisposable disposable = this._LBuff as IDisposable;
       	// if (disposable != null) { disposable.Dispose(); }
       	_LBuff.clear();
    }
}

//char* MarshalEndian:: Encode(IBaseMessage msg)
int MarshalEndian:: Encode(BaseMessage* msg,char *buf)
{
	char *msgBuffer = msg->GetByte();
	ofstream bw(buf, ios::binary);

	//#pragma region 封装包头  
    bw.write((char *)&t1,sizeof(t1));
    bw.write((char *)&t2,sizeof(t2));
	//#pragma endregion

	short len = 0;
	//#region 包协议  
    if (msg != NULL)
    {
    	len = sizeof(msgBuffer) + 4;
        bw.write((char *)&len,sizeof(len));
        bw.write((char *)&msg->MsgID,sizeof(msg->MsgID));
        bw.write(msgBuffer,sizeof(msgBuffer));
    }
    else
    {
    	bw.write((char *)&len,sizeof(len));
    }
	//#endregion

    return 0;
}

// 得到一个完整的数据包
void MarshalEndian::  handleDataUint(char *dataUnit, int size)
{
  	//得到数据之后，在这里进行拼包或者进行下一步处理等操作
  	int MsgID;
  	char buf[size - 4];
  	memcpy(&MsgID,dataUnit,4);
  	memcpy(buf,dataUnit + 4,size - 4);

  	printf(">>>>>>>>>>>>  recv msgID : %d\n",MsgID);
   	//coreMoudles->get_busMDL()->Process(MsgID,buf);


	protobufMsg:: Person p;

    p.ParseFromString(buf);

	cout << "write buf length = " << size << "\t";
	cout << "id = " << p.id() << "\t";
	cout << "name = " << p.name() << "\t";
	cout << "email = " << p.email() << "\t" << endl;
}
int MarshalEndian:: Decode(char *server_reply, int readSize)
{
    memcpy(recbuff + buffsize, server_reply, readSize);//memcpy为内存拷贝函数，将该次接收到的server_reply的数据拷贝到recbuff里
	//其中+buffsize，从recbuff头地址+buffsize的地址开始拷贝（第一次buffsize=0，及从头开始拷贝）拷贝的大小为readSize，即recv实际接收到的数据大小。
    buffsize += readSize;//buffsize=buffsize+readSize，此时buffsize指向该次拷贝的数据大小的下一位。
    const int packetHeadSize = 4;//定义控制域的数据大小为8个字节
    static int expectedPacketSize = -1;//定义期望得到的数据包大小为-1，以此判断本次接收到的数据是否是数据头部
    if (expectedPacketSize == -1 && buffsize >= packetHeadSize)
    {//接收到的数据比8个字节大，即包含了控制域及数据域，则进行下一步分析
        //start token must be 0x0628, otherwise reconnect!
        unsigned char t0 = recbuff[0];//取出接收数据的前两个字节
        unsigned char t1 = recbuff[1];
        assert(t0 == 0x28 && t1 == 0x06);//判断是否为0628H，是否符合启动字符条件，注意小端对齐
        if (!(t0 == 0x28 && t1 == 0x06))//如果不是0628H，则表示该次数据有误
        {
            return 1;
        }
        //find packet length!!

        unsigned short len = 0;//定义报文长度
        memcpy(&len, recbuff + 2, 2);//将接收数据的下第三第四个字节付给len，根据协议第三第四个字节存储的是该帧报文的长度
        expectedPacketSize = len + packetHeadSize;//则期望得到的数据包大小为报文长度加控制域长度
    }

    //get one whole packet!
    if (expectedPacketSize != -1 && (int)buffsize >= expectedPacketSize)
    {
    	//当期望得到的数据包大小不是-1
        // 并且recbuff里接收到的数据大小已经大于所需要的数据大小，如果接收到的数据小于完整报文的长度，则继续接收
        //
        //下面为接收到的完整的一帧报文，定义了一个解包函数负责解包，从缓存数据的第9个字节开始取，取完整数据域长度的数据，即只取数据域的内容
        handleDataUint(recbuff + packetHeadSize, expectedPacketSize -packetHeadSize);
		//下面的memmove函数是内存移动函数，将下一帧报文移动到recbuff的起始处，覆盖掉已经取出的数据
        memmove(recbuff, recbuff + expectedPacketSize, buffsize - expectedPacketSize);
        buffsize -= expectedPacketSize;
        expectedPacketSize = -1;
    }

	return 0;
}


//*************************************************************************************




































