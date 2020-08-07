//
// Created by diego on 05/08/2020.
//
#ifdef BB_LINUX_PLATFORM

#include "LinuxWindow.h"
#include <Events/ApplicationEvent.h>
#include <Events/KeyEvent.h>
#include <Events/MouseEvent.h>

#include <Platform/OpenGL/OpenGLContext.h>

#include <Core/Log.h>

namespace BlackboardRuntime {
    static bool sGLFWInitialized = false;

    static void GLFWErrorCallback(int error, const char* description) {
        BB_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    Ref<Window> Window::Create(const WindowProperties& props) { return CreateRef<LinuxWindow>(props); }
    LinuxWindow::LinuxWindow(const WindowProperties& props) { Init(props); }

    LinuxWindow::~LinuxWindow() { Shutdown(); }

    void LinuxWindow::Init(const WindowProperties& props) {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        BB_CORE_INFO("Creating Window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if (!sGLFWInitialized)
        {
            int success = glfwInit();
            BB_CORE_ASSERT(success, "Could not initialize GLFW!");

            glfwSetErrorCallback(GLFWErrorCallback);
            sGLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);

        m_Context = new OpenGLContext(m_Window);
        m_Context->Init();

        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizedEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            KeyTypedEvent event(keycode);
            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });

    }

    void LinuxWindow::Shutdown() { glfwDestroyWindow(m_Window); }

    void LinuxWindow::OnUpdate() {
        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    void LinuxWindow::SetVSync(bool enabled) {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = enabled;
    }

    bool LinuxWindow::IsVSync() const { return m_Data.VSync; }

    void LinuxWindow::SetWindowSubtitle(const std::string &subtitle) {
        std::stringstream combinedTitle;
        combinedTitle << m_Data.Title;
        combinedTitle << " - ";
        combinedTitle << subtitle;
        glfwSetWindowTitle(m_Window, combinedTitle.str().c_str());
    }
}
#endif