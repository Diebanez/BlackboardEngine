//
// Created by diego on 24/07/2020.
//

#ifndef BLACKBOARDENGINE_KEYEVENT_H
#define BLACKBOARDENGINE_KEYEVENT_H

#include "Event.h"
#include <sstream>

namespace BlackboardRuntime {
    class KeyEvent : public Event {
    public:
        inline int GetKeyCode() const { return mKeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        KeyEvent(int keyCode) : mKeyCode(keyCode) {}

        int mKeyCode;
    };

    class KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), mRepeatCount(repeatCount) {}

        inline int GetRepeatCount() const { return mRepeatCount; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << mKeyCode << " (" << mRepeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)

    private:
        int mRepeatCount;
    };

    class KeyReleasedEvent : public KeyEvent {
    public:
        KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << mKeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class KeyTypedEvent : public KeyEvent {
    public:
        KeyTypedEvent(int keyCode) : KeyEvent(keyCode) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << mKeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };
}

#endif //BLACKBOARDENGINE_KEYEVENT_H
