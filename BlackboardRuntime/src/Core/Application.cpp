#include <Events/EventDispatcher.h>
#include <Events/ApplicationEvent.h>
#include "Application.h"
#include "Log.h"

namespace BlackboardRuntime
{
#define BIND_EVENT(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::m_Instance = nullptr;

    Application::Application() : m_Running(true) {
        m_Instance= this;
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT(OnEvent));
    }

    Application::~Application() { }

    void Application::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(OnWindowClose));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }

    void Application::Run(){
        while(m_Running){
            m_Window->OnBeforeUpdate();

            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();
            for (Layer* layer : m_LayerStack)
                layer->OnBeforeGuiRender();
            for (Layer* layer : m_LayerStack)
                layer->OnGuiRender();
            for (Layer* layer : m_LayerStack)
                layer->OnAfterGuiRender();

            m_Window->OnUpdate();
        }
        BB_CORE_INFO("Closing");
    }

    void Application::PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }

    void Application::PushOverlay(Layer* layer) { m_LayerStack.PushOverlay(layer); }

    bool Application::OnWindowClose(WindowCloseEvent& e) {
        m_Running = false;
        return true;
    }
} // namespace BlackboardRuntime