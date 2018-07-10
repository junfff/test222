#include "../../include/Business/BusinessModule.h"
#include "../../include/Base/IModulesCollection.h"
#include "../../include/Business/PersonBusiness.h"
#include <stdlib.h>
#include <stdio.h>
using namespace GameBase;
namespace Business
{
	void BusinessModule::Initialize()
	{
		bus_v.push_back(new PersonBusiness(1));

	}
	void BusinessModule::Dispose()
	{
		bus_v.clear();
		bus_v.shrink_to_fit();
	}
	int BusinessModule:: Process(int MsgID,char *buf,void *ev)
	{
		size_t len = bus_v.size();
    	for (size_t i =0; i < len; i ++)
    	{
        	IBusiness *b = bus_v[i];
        	if(b->Get_ID() == MsgID)
        	{
        		b->Process(buf,ev);
        	}
    	}

		printf("not find business !!!! MsgID:%d\n",MsgID);
		return -1;
	}

}
