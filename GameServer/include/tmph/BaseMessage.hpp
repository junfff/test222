/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：BaseMseeage.hpp
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年07月10日 16:20(Tuesday) 
 *   描    述：
 *
 ================================================================*/


#ifndef _BASEMSEEAGE_H
#define _BASEMSEEAGE_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "Interface.hpp"

	Interface BaseMessage
	{
		public:
			int MsgID;
     		char *GetByte();
	};


#ifdef __cplusplus
}
#endif
#endif //BASEMSEEAGE_H
