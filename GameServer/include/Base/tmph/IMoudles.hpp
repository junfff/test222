/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：IMoudles.hpp
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年07月10日 16:29(Tuesday) 
 *   描    述：
 *
 ================================================================*/


#ifndef _IMOUDLES_H
#define _IMOUDLES_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "Interface.hpp"
#include "GameBase.hpp"
	class IMoudlesCollection;
	//#include "IMoudlesCollection.hpp"

	namespace GameBase
	{

		Interface ICoreMoudles
		{
			public:
				virtual ~ICoreMoudles(){}
				virtual  IMoudlesCollection *get_CoreMoudles() = 0;
		};
		Interface IMoudles : implements IInitialize,implements IDisposable,implements ICoreMoudles
		{
			public:
				virtual ~IMoudles(){}

		};
	}
#ifdef __cplusplus
}
#endif
#endif //IMOUDLES_H
