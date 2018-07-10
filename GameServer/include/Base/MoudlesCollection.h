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
//#include "IMoudles.h"
#include "IMoudlesCollection.h"
#include <vector>
using namespace std;
namespace GameBase
{
	class MoudlesCollection : implements IMoudlesCollection
	{
		public:

			void Initialize() override;
			void Dispose() override;
	 		IBusinessMoudle *get_busMDL() override;
		 	IMarshalEndian *get_Ime() override;

		private:
	 		IBusinessMoudle *busMDL;
	 		IMarshalEndian *Ime;

	 		vector<IMoudles *> moudles_v;
	};
}
