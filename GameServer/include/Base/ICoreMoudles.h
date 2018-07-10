/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：IMoudles.h
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年07月10日 16:06(Tuesday) 
 *   描    述：
 *
 ================================================================*/


#ifndef _ICOREMOUDLES_H
#define _ICOREMOUDLES_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "../Interface.h"
#include "GameBase.h"      
#include "IMoudlesCollection.h"
	//class IMoudlesCollection;
  	namespace GameBase         
 	{
     	Interface ICoreMoudles 
     	{
         	public:            
             	virtual ~ICoreMoudles(){}       
             	virtual  IMoudlesCollection *get_CoreMoudles() = 0;
      	};
  	}

#ifdef __cplusplus
}
#endif
#endif //IMOUDLES_H
