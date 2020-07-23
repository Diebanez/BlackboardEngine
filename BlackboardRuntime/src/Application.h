namespace BlackboardRuntime
{
    class Application
    {
    public:
        Application(unsigned int tickCount);
        bool Run();

    private:
        unsigned int m_ActualTickCount;
        unsigned int m_MaxTickCount;
    };
} // namespace BlackboardRuntime