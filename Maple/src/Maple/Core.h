#pragma once

#ifdef MP_PLATFORM_WINDOWS
	#ifdef MP_BUILD_DLL
		#define MAPLE_API __declspec(dllexport)
	#else
		#define MAPLE_API __declspec(dllimport)
	#endif
#else
	#error Maple currently only supports Windows!
#endif

#ifdef MP_ENABLE_ASSERTS
	#define MP_ASSERT(x, ...) {if(!(x)) {MP_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define MP_CORE_ASSERT(x, ...) {if(!(x)) {MP_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define MP_ASSERT(x, ...)
	#define MP_CORE_ASSERT(x, ...)
#endif

#define MP_BIND_EVENT_FN(func) std::bind(&func, this, std::placeholders::_1)

#define BIT(x) (1 << x)