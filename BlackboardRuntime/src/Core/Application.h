#include "Events/Event.h"
#include "Layer.h"
#include "LayerStack.h"

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
    private:
        bool OnWindowClose(WindowCloseEvent& e);

        static Application* m_Instance;

        bool m_Running = true;
        LayerStack m_LayerStack;
    };

    Application* CreateApplication();
} // namespace BlackboardRuntime