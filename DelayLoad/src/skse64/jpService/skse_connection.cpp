#include "common/IDebugLog.h"
#include "skse64_common/skse_version.h"
#include "skse64/PluginAPI.h"

#include <ShlObj.h>

extern "C"
{
	__declspec(dllexport) bool SKSEPlugin_Query(const SKSEInterface* a_skse, PluginInfo* a_info)
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition\\SKSE\\jpService.log");
		gLog.SetPrintLevel(IDebugLog::kLevel_DebugMessage);
		gLog.SetLogLevel(IDebugLog::kLevel_DebugMessage);

		a_info->infoVersion = PluginInfo::kInfoVersion;
		a_info->name = "jpService";
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
		_MESSAGE("jpService loaded");

		return true;
	}
};
