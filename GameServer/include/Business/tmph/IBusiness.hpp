/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：IBusiness.hpp
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年07月10日 16:34(Tuesday) 
 *   描    述：
 *
 ================================================================*/


#ifndef _IBUSINESS_H
#define _IBUSINESS_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "Interface.hpp"
	Interface IBusiness
	{
		public:
			virtual ~IBusiness(){}
			virtual int Get_ID() = 0;
        	virtual int Set_ID() = 0;
			virtual int Process(char *buf) = 0;
	};
#ifdef __cplusplus
}
#endif
#endif //IBUSINESS_H
