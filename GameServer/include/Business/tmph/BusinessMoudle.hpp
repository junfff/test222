/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：BusinessMoudle.hpp
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年07月10日 16:33(Tuesday) 
 *   描    述：
 *
 ================================================================*/


#ifndef _BUSINESSMOUDLE_H
#define _BUSINESSMOUDLE_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "IBusiness.hpp"
#include "../Base/IBusinessMoudle.hpp"
	using namespace GameBase;

	namespace Business
	{
		class BusinessMoudle : implements IBusinessMoudle
		{
			public:
				IMoudlesCollection *coreMoudles;
				void Initialize() override;
				void Dispose() override;
		  		IMoudlesCollection *get_CoreMoudles() override;
				int Process(int MsgID,char *buf) override;

			private:
				int bus_len;
				IBusiness *bus_set;//声明
		};
	}
#ifdef __cplusplus
}
#endif
#endif //BUSINESSMOUDLE_H
