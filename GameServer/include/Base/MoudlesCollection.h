/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：MoudlesCollection.h
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年07月09日 20:39(Monday) 
 *   描    述：
 *
 ================================================================*/


#pragma once
#include "IMoudlesCollection.h"

class MoudlesCollection : implements IMoudlesCollection
{
	public:

		void Initialize() override;
		void Dispose() override;
	 	IBusinessMoudle *get_busMDL() override;
	private:
	 	IBusinessMoudle *busMDL;
};
