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
		int Decode(char *buff, int len,list<BaseMessage> ls) override;

	protected:
		void Dispose(bool flag1);
	private:

		//用于存储剩余未解析的字节数  
		list<char> _LBuff;
		//默认是utf8的编码格式  
 		//UTF8Encoding utf8;
		//包头1  
		const short t1 = 0x55;
		//包头2  
		const short t2 = 0xAA;
		//字节数常量 两个包头4个字节，一个消息id4个字节，封装消息长度 int32 4个字节  
		const int ConstLenght = 8;

		//public IRemote Context { get; set; }

};
