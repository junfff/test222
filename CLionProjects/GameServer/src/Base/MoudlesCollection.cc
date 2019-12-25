#include "../include/Base/ModulesCollection.h"
#include "../include/Business/BusinessModule.h"
#include "../include/MarshalEndian.h"
#include "../include/Base/GameBase.h"
using namespace Business;
namespace GameBase
{
	ModulesCollection::ModulesCollection()
	{
	}
	void ModulesCollection::Initialize()
	{
		modules_v.push_back(busMDL = new BusinessModule());
		//moudles_v.push_back(Ime = new MarshalEndian());
		size_t len = modules_v.size();
    	for (size_t i =0; i < len; i ++)
    	{
        	IModules *b = modules_v[i];
        	b->Initialize();
    	}
	}
	void ModulesCollection::Dispose()
	{
		size_t len = modules_v.size();
    	for (size_t i =0; i < len; i ++)
    	{
        	IModules *b = modules_v[i];
        	b->Dispose();
    	}
		modules_v.clear();
		modules_v.shrink_to_fit();
	}
	IBusinessModule *ModulesCollection::get_busMDL()
	{
		return busMDL;
	}
}
