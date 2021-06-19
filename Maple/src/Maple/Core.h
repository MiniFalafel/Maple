#pragma once

#ifdef MP_PLATFORM_WINDOWS
	#ifdef MP_BUILD_DLL
		#define MAPLE_API __declspec(dllexport)
	#else
		#define MAPLE_API __declspec(dllimport)
	#endif
#else
	#error Maple Currently only supports Windows!
#endif

#define BIT(x) (1 << x)
