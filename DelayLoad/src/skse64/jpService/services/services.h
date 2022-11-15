#pragma once

#ifdef JPSERVICE_EXPORTS
#  define JPSERVICE_API __declspec(dllexport)
#else
#  define JPSERVICE_API __declspec(dllimport)
#endif

namespace jp_services
{
	class JPSERVICE_API Test
	{
	public:
		int getval();
	};

	extern "C"
	{
		JPSERVICE_API SInt32 GetSmth();
	}
}
