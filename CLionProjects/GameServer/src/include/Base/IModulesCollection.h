/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：IModulesCollection.h
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年07月09日 20:03(Monday) 
 *   描    述：
 *
 ================================================================*/


#pragma once
#include "GameBase.h"
#include "IBusinessModule.h"
#include "../IMarshalEndian.h"


namespace GameBase
{
	Interface IModulesCollection : implements IInitialize, implements IDisposable
	{
		public:
			virtual ~IModulesCollection(){}

			virtual IBusinessModule *get_busMDL() = 0;
	};

}
