/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：IBusinessMoudle.h
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年07月09日 20:08(Monday) 
 *   描    述：
 *
 ================================================================*/


#pragma once
#include "../Interface.h"
#include "IMoudles.h"

namespace GameBase
{
	Interface IBusinessMoudle : implements IMoudles
	{
		public:
			virtual ~IBusinessMoudle(){}

			virtual int Process(int MsgID,char *buf) = 0;
	};
}
