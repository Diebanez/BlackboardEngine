//
// Created by diego on 24/07/2020.
//

#include "Log.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace BlackboardRuntime{
    std::shared_ptr<spdlog::logger> Log::m_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::m_ClientLogger;

    void Log::Init(){
        spdlog::set_pattern("%^[%T] %n: %v%$");

        m_CoreLogger = spdlog::stdout_color_mt("RUNTIME");
        m_CoreLogger->set_level(spdlog::level::trace);

        m_ClientLogger = spdlog::stdout_color_mt("APP");
        m_ClientLogger->set_level(spdlog::level::trace);

        BB_CORE_INFO("Initialized Logger!");
    }

}