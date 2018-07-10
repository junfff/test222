#include "../../include/Business/BusinessMoudle.h"
#include "../../include/Base/IMoudlesCollection.h"
#include <stdlib.h>
using namespace GameBase;
namespace Business
{
	IMoudlesCollection *BusinessMoudle::get_CoreMoudles()
	{
		return coreMoudles;
	}

	void BusinessMoudle::Initialize()
	{
	}
	void BusinessMoudle::Dispose()
	{
	}
	int BusinessMoudle:: Process(int MsgID,char *buf)
	{
		for(int i=0;i<bus_len;i++)
		{
			if(bus_set[i].Get_ID() == MsgID)
			{
				return bus_set[i].Process(buf);
			}
		}
		return -1;
	}

}
