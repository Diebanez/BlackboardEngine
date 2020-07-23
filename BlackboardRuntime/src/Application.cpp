#include "Application.h"
#include "Log.h"

namespace BlackboardRuntime
{
    Application* Application::m_Instance = nullptr;

    Application::Application() : m_Running(true) {
        m_Instance= this;
    }

    Application::~Application() { }

    void Application::Run(){
        while(m_Running){
            BB_CORE_INFO("Running");
        }
        BB_CORE_INFO("Closing");
    }
} // namespace BlackboardRuntime