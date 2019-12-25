/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：IBaseMessage.h
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年06月22日 21:00(Friday) 
 *   描    述：
 *
 ================================================================*/


#pragma once

#include "Interface.h"

Interface BaseMessage
{
	public:
		int MsgID;
     	char *GetByte(); 
};
