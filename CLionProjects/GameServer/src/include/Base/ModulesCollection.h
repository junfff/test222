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
#include "IModulesCollection.h"
#include <vector>
#include "IModules.h"

using namespace std;
namespace GameBase
{
	class ModulesCollection : implements IModulesCollection
	{
		public:
			ModulesCollection();
			//~ModulesCollection() override;

			void Initialize() override;
			void Dispose() override;
	 		IBusinessModule *get_busMDL() override;

		private:
	 		IBusinessModule *busMDL;
	 		IMarshalEndian *Ime;

	 		vector<IModules *> modules_v;
	};
}
