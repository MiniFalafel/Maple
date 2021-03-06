#pragma once

#include "Maple/Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Maple {

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

}

// Core Logging Macros
#define MP_CORE_TRACE(...)   ::Maple::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MP_CORE_INFO(...)    ::Maple::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MP_CORE_WARN(...)    ::Maple::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MP_CORE_ERROR(...)   ::Maple::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MP_CORE_CRITICAL(...)   ::Maple::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client Logging Macros
#define MP_TRACE(...)        ::Maple::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MP_INFO(...)         ::Maple::Log::GetClientLogger()->info(__VA_ARGS__)
#define MP_WARN(...)         ::Maple::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MP_ERROR(...)        ::Maple::Log::GetClientLogger()->error(__VA_ARGS__)
#define MP_CRITICAL(...)        ::Maple::Log::GetClientLogger()->critical(__VA_ARGS__)
