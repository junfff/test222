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
#include "Interface.h"
#include "IBusinessMoudle.h"

Interface IMoudlesCollection : implements IInitialize, implements IDisposable
{
	public:
		virtual ~IMoudlesCollection(){}

		virtual IBusinessMoudle *get_busMDL() = 0;
};


