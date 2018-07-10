/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：MoudlesCollection.hpp
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年07月10日 16:32(Tuesday) 
 *   描    述：
 *
 ================================================================*/


#ifndef _MOUDLESCOLLECTION_H
#define _MOUDLESCOLLECTION_H
//#include <vector>
#ifdef __cplusplus
extern "C"
{
#endif
#include "IMoudlesCollection.hpp"
#include "IMoudles.hpp"
	//using namespace std;
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

	 			//vector<IMoudles *> moudles_v;
		};
	}
#ifdef __cplusplus
}
#endif
#endif //MOUDLESCOLLECTION_H
