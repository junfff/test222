/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：IMoudles.h
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年07月10日 16:06(Tuesday) 
 *   描    述：
 *
 ================================================================*/


#ifndef _IMOUDLES_H
#define _IMOUDLES_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "../Interface.h"
#include "GameBase.h"      
#include "ICoreMoudles.h"

  	namespace GameBase         
 	{
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
