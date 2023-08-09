#pragma once

#ifdef MYENGINE_PLATFORM_WINDOWS
	#ifdef MYENGINE_BUILD_DLL
		#define MYENGINE_API __declspec(dllexport)
	#else
		#define MYENGINE_API __declspec(dllimport)
	#endif // MYENGINE_BUILD_DLL
#else
	#error "MyEngine is only for Windows..."
#endif // MYENGINE_PLATFORM_WINDOWS

#define BIT(x) (1 << x)