#pragma once

#include <memory>

// Platform detection
#ifdef _WIN32
	#ifdef _WIN64
		#define MP_PLATFORM_WINDOWS
	#else
		#error "Win32 (x86) is not supported!"
	#endif

#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define MP_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define MP_PLATFORM_MAC
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif

#elif defined (__ANDROID__)
	#define MP_PLATFORM_ANDROID
	#error "Android is not supported!"

#elif defined(__linux__)
	#define MP_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	#error "Unknown platform!"
#endif

// Optional for DLL builds
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
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}
