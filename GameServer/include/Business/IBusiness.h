/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：IBusiness.h
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年07月09日 16:05(Monday) 
 *   描    述：
 *
 ================================================================*/


#pragma once

#include "Interface.h"
Interface IBusiness
{
	public:
		virtual ~IBusiness(){}
		virtual int Get_ID() = 0;
        virtual int Set_ID() = 0;
		virtual int Process(char *buf) = 0;
};
