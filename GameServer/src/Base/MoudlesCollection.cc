#include "../../include/Base/ModulesCollection.h"
#include "../../include/Business/BusinessModule.h"
#include "../../include/MarshalEndian.h"
#include "../../include/Base/GameBase.h"
using namespace Business;
namespace GameBase
{
	ModulesCollection::ModulesCollection()
	{
	}
	void ModulesCollection::Initialize()
	{
		//moudles_v.push_back(busMDL = new BusinessMoudle());
		//moudles_v.push_back(Ime = new MarshalEndian());
	}
	void ModulesCollection::Dispose()
	{
	}
	IBusinessModule *ModulesCollection::get_busMDL()
	{
		return busMDL;
	}
}
