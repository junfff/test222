/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：Businessmoudle.h
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年07月09日 16:04(Monday) 
 *   描    述：
 *
 ================================================================*/


#pragma once
#include "IBusiness.h"
#include "../Base/IBusinessMoudle.h"
using namespace GameBase;

namespace Business
{
	class BusinessMoudle : implements IBusinessMoudle
	{
		public:
			IMoudlesCollection *coreMoudles;
			void Initialize() override;
			void Dispose() override;
		  	IMoudlesCollection *get_CoreMoudles() override;
			int Process(int MsgID,char *buf) override;

		private:
			int bus_len;
			IBusiness *bus_set;//声明
	};
}
