//
// Created by diego on 24/07/2020.
//

#ifndef BLACKBOARDENGINE_WINDOWS_H
#define BLACKBOARDENGINE_WINDOWS_H

#include <string>
#include <functional>
#include <Events/Event.h>

namespace BlackboardRuntime{
    struct WindowProperties{
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProperties(const std::string& title = "Blackboard Engine", unsigned int width = 1920, unsigned int height = 1080)
        : Title(title), Width(width), Height(height){}
    };

    class Window{
    public:
        using EventCallbackFunction = std::function<void(Event&)>;

        virtual ~Window(){}

        virtual void OnUpdate() = 0;
        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallbackFunction& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void* GetNativeWindow() const = 0;

        static Window* Create(const WindowProperties& props = WindowProperties());
    };
}

#endif //BLACKBOARDENGINE_WINDOWS_H
