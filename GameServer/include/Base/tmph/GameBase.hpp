/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：GameBase.hpp
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年07月10日 16:28(Tuesday) 
 *   描    述：
 *
 ================================================================*/


#ifndef _GAMEBASE_H
#define _GAMEBASE_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "Interface.hpp"
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
#ifdef __cplusplus
}
#endif
#endif //GAMEBASE_H
