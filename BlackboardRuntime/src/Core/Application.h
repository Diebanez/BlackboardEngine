#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Layer.h"
#include "LayerStack.h"
#include "TimeStep.h"
#include <memory>
#include <Rendering/Window.h>
#include <Rendering/Camera/OrthographicCamera.h>

namespace BlackboardRuntime
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void OnEvent(Event& e);
        void Run();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline static Application& Get() { return *m_Instance; }
        inline Window& GetWindow() { return *m_Window; }

    private:
        bool OnWindowClose(WindowCloseEvent& e);

        static Application* m_Instance;

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;
        float m_LastFrameTime = 0.0f;
        float m_LastTitleUpdateCount = 0;
    };

    Application* CreateApplication();
} // namespace BlackboardRuntime
