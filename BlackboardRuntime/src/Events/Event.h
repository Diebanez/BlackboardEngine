//
// Created by diego on 24/07/2020.
//

#ifndef BLACKBOARDENGINE_EVENT_H
#define BLACKBOARDENGINE_EVENT_H

#include "Core/Core.h"
#include <iostream>

namespace BlackboardRuntime{
    enum class EventType {
        None = 0,

        //Window
        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,

        //App
        AppTick,
        AppUpdate,
        AppRender,

        //Key
        KeyPressed,
        KeyReleased,
        KeyTyped,

        //Mouse
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled
    };

    enum EventCategory
    {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

    class Event{
    public:
        bool Handled = false;
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const {return GetName();}

        inline bool IsInCategory(EventCategory category){
            return GetCategoryFlags() & category;
        }
    };
    
    inline std::ostream& operator<<(std::ostream& os, const Event& e) {
        return os << e.ToString();
    }
}

#endif //BLACKBOARDENGINE_EVENT_H
