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
#include "../Base/IBusinessModule.h"
#include "../Base/IModulesCollection.h"
#include <vector>
using namespace GameBase;

namespace Business
{
	class BusinessModule : implements IBusinessModule
	{
		public:
			IModulesCollection *coreModules;
			void Initialize() override;
			void Dispose() override;
		 	// 	IModulesCollection *get_CoreModules() override;
			int Process(int MsgID,char *buf,void *ev) override;

		private:
			int bus_len;
	 		vector<IBusiness *> bus_v;
	};
}
