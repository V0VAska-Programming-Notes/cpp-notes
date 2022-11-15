#include "funcs.h"
#include "jpService/services/services.h"

//#include "skse64/PapyrusArgs.h"
//#include "skse64/GameRTTI.h"

namespace jp_client
{
	SInt32 GetIntFromService(StaticFunctionTag* base)
	{
		//return 10;
		return jp_services::GetSmth();
	}
}

bool jp_client::RegisterFuncs(VMClassRegistry* registry)
{
	registry->RegisterFunction(
		new NativeFunction0<StaticFunctionTag, SInt32>("GetIntFromService", "jp_test_funcs", jp_client::GetIntFromService, registry)
	);
	return true;
}
