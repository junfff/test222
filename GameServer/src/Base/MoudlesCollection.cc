#include "../../include/Base/MoudlesCollection.h"
#include "../../include/Business/BusinessMoudle.h"
#include "../../include/MarshalEndian.h"
#include "../../include/Base/GameBase.h"
using namespace Business;
namespace GameBase
{
	void MoudlesCollection::Initialize()
	{
		//moudles_v.push_back(busMDL = new BusinessMoudle());
		//moudles_v.push_back(Ime = new MarshalEndian());
	}
	void MoudlesCollection::Dispose()
	{
	}
	IBusinessMoudle *MoudlesCollection::get_busMDL()
	{
		return busMDL;
	}
	IMarshalEndian *MoudlesCollection::get_Ime()
	{
		return Ime;
	}
}
