#pragma once

#include <memory>
#include <spdlog/spdlog.h>
#include "Engine/Core.hpp"

namespace my
{
	class MYENGINE_API Log
	{
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_clientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};
}

#define MYENGINE_CORE_FATAL(...) my::Log::getCoreLogger()->fatal(__VA_ARGS__)
#define MYENGINE_CORE_ERROR(...) my::Log::getCoreLogger()->error(__VA_ARGS__)
#define MYENGINE_CORE_WARN(...) my::Log::getCoreLogger()->warn(__VA_ARGS__)
#define MYENGINE_CORE_INFO(...) my::Log::getCoreLogger()->info(__VA_ARGS__)
#define MYENGINE_CORE_TRACE(...) my::Log::getCoreLogger()->trace(__VA_ARGS__)

#define MYENGINE_CLIENT_FATAL(...) my::Log::getClientLogger()->fatal(__VA_ARGS__)
#define MYENGINE_CLIENT_ERROR(...) my::Log::getClientLogger()->error(__VA_ARGS__)
#define MYENGINE_CLIENT_WARN(...) my::Log::getClientLogger()->warn(__VA_ARGS__)
#define MYENGINE_CLIENT_INFO(...) my::Log::getClientLogger()->info(__VA_ARGS__)
#define MYENGINE_CLIENT_TRACE(...) my::Log::getClientLogger()->trace(__VA_ARGS__)