/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：IMoudlesCollection.hpp
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年07月10日 16:31(Tuesday) 
 *   描    述：
 *
 ================================================================*/


#ifndef _IMOUDLESCOLLECTION_H
#define _IMOUDLESCOLLECTION_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "GameBase.hpp"
#include "IBusinessMoudle.hpp"
	class IMarshalEndian;
	//#include "IMarshalEndian.hpp"
	namespace GameBase
	{
		Interface IMoudlesCollection : implements IInitialize, implements IDisposable
		{
			public:
				virtual ~IMoudlesCollection(){}

				virtual IBusinessMoudle *get_busMDL() = 0;
				virtual IMarshalEndian *get_Ime() = 0;
		};

	}
#ifdef __cplusplus
}
#endif
#endif //IMOUDLESCOLLECTION_H
