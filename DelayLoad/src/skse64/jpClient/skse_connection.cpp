#include "common/IDebugLog.h"
#include "skse64_common/skse_version.h"
#include "skse64/PluginAPI.h"

#include <ShlObj.h>

#include "jpClient/funcs/funcs.h"

extern "C"
{
	__declspec(dllexport) bool SKSEPlugin_Query(const SKSEInterface* a_skse, PluginInfo* a_info)
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition\\SKSE\\jpClient.log");
		gLog.SetPrintLevel(IDebugLog::kLevel_DebugMessage);
		gLog.SetLogLevel(IDebugLog::kLevel_DebugMessage);

		a_info->infoVersion = PluginInfo::kInfoVersion;
		a_info->name = "jpClient";
		a_info->version = 1;

		if (a_skse->isEditor)
		{
			_FATALERROR("[FATAL ERROR] Loaded in editor, marking as incompatible!\n");
			return false;
		}
		else if (a_skse->runtimeVersion != RUNTIME_VERSION_1_5_97)
		{
			_FATALERROR("[FATAL ERROR] Unsupported runtime version %08X!\n", a_skse->runtimeVersion);
			return false;
		}
		return true;
	}


	__declspec(dllexport) bool SKSEPlugin_Load(const SKSEInterface* a_skse)
	{
		_MESSAGE("jpClient loaded");

		SKSEPapyrusInterface* g_papyrus = (SKSEPapyrusInterface*)a_skse->QueryInterface(kInterface_Papyrus);
		bool bResult = g_papyrus->Register(jp_client::RegisterFuncs);

		return true;
	}
};
