#include "../../include/Business/BusinessMoudle.h"
#include <stdlib.h>

int Business_Process(int MsgID,char *buf)
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



void Business_Init()
{
   	bus_set = (IBusiness *)malloc(sizeof(IBusiness) * 11);
}
void Business_Deinit()
{
}
