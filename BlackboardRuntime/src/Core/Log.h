//
// Created by diego on 24/07/2020.
//
#pragma once
#ifndef BLACKBOARDENGINE_LOG_H
#define BLACKBOARDENGINE_LOG_H

#include "spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace BlackboardRuntime {
    class Log {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_CoreLogger; }

        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> m_CoreLogger;
        static std::shared_ptr<spdlog::logger> m_ClientLogger;
    };
}

#define BB_CORE_TRACE(...) ::BlackboardRuntime::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BB_CORE_INFO(...) ::BlackboardRuntime::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BB_CORE_WARN(...) ::BlackboardRuntime::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BB_CORE_ERROR(...) ::BlackboardRuntime::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BB_CORE_FATAL(...)::BlackboardRuntime::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define BB_TRACE(...) ::BlackboardRuntime::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BB_INFO(...)::BlackboardRuntime::Log::GetClientLogger()->info(__VA_ARGS__)
#define BB_WARN(...)::BlackboardRuntime::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BB_ERROR(...) ::BlackboardRuntime::Log::GetClientLogger()->error(__VA_ARGS__)
#define BB_FATAL(...) ::BlackboardRuntime::Log::GetClientLogger()->fatal(__VA_ARGS__)

#endif //BLACKBOARDENGINE_LOG_H
