/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：GameBase.h
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年07月09日 20:33(Monday) 
 *   描    述：
 *
 ================================================================*/


#pragma once
#include "../Interface.h"
//#include "IMoudlesCollection.h"
namespace GameBase
{
	Interface IInitialize
	{
		public:
			virtual ~IInitialize(){}

			virtual void Initialize() = 0;
	};
	Interface IDisposable
	{
		public:
			virtual ~IDisposable(){}

			//
        	// 摘要:
        	//     Performs application-defined tasks associated with freeing, releasing, or resetting
        	//     unmanaged resources.
       		virtual void Dispose() = 0;
	};

}
