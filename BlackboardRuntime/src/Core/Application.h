#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Layer.h"
#include "LayerStack.h"
#include <Rendering/Window.h>

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
    };

    Application* CreateApplication();
} // namespace BlackboardRuntime