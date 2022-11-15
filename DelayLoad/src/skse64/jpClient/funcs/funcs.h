#pragma once

//#include "skse64/GameForms.h"
#include "skse64/PapyrusNativeFunctions.h"

namespace jp_client
{
	SInt32 GetIntFromService(StaticFunctionTag* base);

	bool RegisterFuncs(VMClassRegistry* registry);
}
