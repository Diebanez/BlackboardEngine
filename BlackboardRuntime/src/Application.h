namespace BlackboardRuntime
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        inline static Application& Get() { return *m_Instance; }
    private:
        static Application* m_Instance;

        bool m_Running = true;
    };

    Application* CreateApplication();
} // namespace BlackboardRuntime