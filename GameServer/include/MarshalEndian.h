/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：MarshalEndian.h
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年06月23日 10:55(Saturday) 
 *   描    述：
 *
 ================================================================*/


#pragma once
#include "IMarshalEndian.h"

class MarshalEndian :implements IMarshalEndian 
{
	public:
		void Initialize() override;
		void Dispose() override;  
		int Encode(BaseMessage *msg,char *buf) override;  
		int Decode(char *buff, int len) override;
		void handleDataUint(char *dataUnit, int size) override;

	protected:
		void Dispose(bool flag1);
	private:

		IMoudlesCollection *coreMoudles;
		//用于存储剩余未解析的字节数  
		list<char> _LBuff;
		//默认是utf8的编码格式  
 		//UTF8Encoding utf8;
		//包头1  
		const short t1 = 0x28;
		//包头2  
		const short t2 = 0x06;
		//字节数常量 两个包头4个字节，一个消息id4个字节，封装消息长度 int32 4个字节  
		const int ConstLenght = 8;

		//public IRemote Context { get; set; }


    	//char server_reply[5000];

    	//Create socket
    	//下面的AF_INET也可以用PF_INET。AF_INET主要是用于互联网地址，而 PF_INET 是协议相关，通常是sockets和端口
    	int rcv_size = 4*640000;    /* 接收缓冲区大小为4*640K */

    	char recbuff[800000];//接收的数据缓存大小，这是我自己设置的区域，为了存放报文
    	unsigned long buffsize = 0 ;
    	//buffsize=0//该值标示当前缓存数据的大小，及下一帧数据存放的地址
};
