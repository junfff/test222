/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：IMarshalEndian.hpp
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年07月10日 16:22(Tuesday) 
 *   描    述：
 *
 ================================================================*/


#ifndef _IMARSHALENDIAN_H
#define _IMARSHALENDIAN_H
//#include <list>
#ifdef __cplusplus
extern "C"
{
#endif

#include "Interface.hpp"
#include "BaseMessage.hpp"
#include "Base/IMoudlesCollection.hpp"

	using namespace GameBase;
	//using namespace std;
	Interface IMarshalEndian : implements IMoudles
	{
		public:
			virtual ~IMarshalEndian(){}
			virtual	void Initialize() = 0;
			virtual	void Dispose() = 0;
			virtual	int Encode(BaseMessage *msg,char *buf) = 0;
			virtual int Decode(char *buff, int len) = 0;
			virtual void handleDataUint(char *dataUnit, int size) = 0;
	};
#ifdef __cplusplus
}
#endif
#endif //IMARSHALENDIAN_H
