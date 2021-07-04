#pragma once

#include <memory>

#ifdef MP_PLATFORM_WINDOWS
#if MP_DYNAMIC_BUILD
	#ifdef MP_BUILD_DLL
		#define MAPLE_API __declspec(dllexport)
	#else
		#define MAPLE_API __declspec(dllimport)
	#endif
#else
	#define MAPLE_API
#endif
#else
	#error Maple currently only supports Windows!
#endif

#ifdef MP_DEBUG
	#define MP_ENABLE_ASSERTS
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

namespace Maple {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
	
}
