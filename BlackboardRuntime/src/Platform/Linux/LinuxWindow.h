//
// Created by diego on 05/08/2020.
//
#ifdef BB_LINUX_PLATFORM
#ifndef BLACKBOARDENGINE_LINUXWINDOW_H
#define BLACKBOARDENGINE_LINUXWINDOW_H

#include <Rendering/Window.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <Rendering/GraphicsContext.h>

namespace BlackboardRuntime {
    class LinuxWindow : public Window{
    public:
        LinuxWindow(const WindowProperties& props);
        virtual ~LinuxWindow();

        void SetWindowSubtitle(const std::string &subtitle) override;


        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return m_Data.Width; }
        inline unsigned int GetHeight() const override { return m_Data.Height; }

        inline void SetEventCallback(const EventCallbackFunction& callback) override { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled);
        bool IsVSync() const override;

    private:
        virtual void Init(const WindowProperties& props);
        virtual void Shutdown();

        inline virtual void* GetNativeWindow() const override { return m_Window; };

        GLFWwindow* m_Window;
        GraphicsContext* m_Context;

        struct WindowData {
            std::string Title;
            unsigned int Width;
            unsigned int Height;
            bool VSync;

            EventCallbackFunction EventCallback;
        };

        WindowData m_Data;
    };

}
#endif //BLACKBOARDENGINE_LINUXWINDOW_H
#endif