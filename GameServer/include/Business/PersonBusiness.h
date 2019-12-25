/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：PersonBusiness.h
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年07月09日 16:13(Monday) 
 *   描    述：
 *
 ================================================================*/


#pragma once

#include "IBusiness.h"
namespace Business
{
	class PersonBusiness :implements IBusiness 
	{
		public:
			PersonBusiness(int id);
        	int Get_ID() override;
			int Process(char *buf,void *ev) override;		
		protected:

		private:
			//MSG ID
			int id;
	};
}
