//
// Created by diego on 24/07/2020.
//
#ifndef BLACKBOARDENGINE_EVENTDISPATCHER_H
#define BLACKBOARDENGINE_EVENTDISPATCHER_H

#include <Events/Event.h>
#include <functional>

namespace BlackboardRuntime {
    class EventDispatcher {
        template<typename T>
        using EventFunction = std::function<bool(T&)>;

    public:
        EventDispatcher(Event &event) : m_Event(event) {}

        template<typename T>
        bool Dispatch(EventFunction<T> function) {
            if (m_Event.GetEventType() == T::GetStaticType()) {
                m_Event.Handled = function(*(T *) &m_Event);
                return true;
            }

            return false;
        }

    private:
        Event &m_Event;
    };
}

#endif //BLACKBOARDENGINE_EVENTDISPATCHER_H
