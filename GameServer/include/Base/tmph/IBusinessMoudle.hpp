/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：IBusinessMoudle.hpp
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年07月10日 16:29(Tuesday) 
 *   描    述：
 *
 ================================================================*/


#ifndef _IBUSINESSMOUDLE_H
#define _IBUSINESSMOUDLE_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "Interface.hpp"
#include "IMoudles.hpp"

	namespace GameBase
	{
		Interface IBusinessMoudle : implements IMoudles
		{
			public:
				virtual ~IBusinessMoudle(){}

				virtual int Process(int MsgID,char *buf) = 0;
		};
	}
#ifdef __cplusplus
}
#endif
#endif //IBUSINESSMOUDLE_H
