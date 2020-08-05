//
// Created by diego on 05/08/2020.
//
#ifdef BB_LINUX_PLATFORM

#include "LinuxInput.h"
#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>
#include <Core/Application.h>

namespace BlackboardRuntime {
    Input* Input::m_Instance = new LinuxInput();

    bool LinuxInput::IsKeyPressedImpl(int keycode) {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS;
    }

    bool LinuxInput::IsKeyDownImpl(int keycode) {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool LinuxInput::IsKeyUpImpl(int keycode) {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_RELEASE;
    }

    bool LinuxInput::IsMouseButtonPressedImpl(int button) {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    bool LinuxInput::IsMouseButtonDownImpl(int button) {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool LinuxInput::IsMouseButtonUpImpl(int button) {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_RELEASE;
    }

    std::pair<float, float> LinuxInput::GetMousePositionImpl() {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double outX;
        double outY;
        glfwGetCursorPos(window, &outX, &outY);
        return { static_cast<float>(outX), static_cast<float>(outY) };
    }
}
#endif