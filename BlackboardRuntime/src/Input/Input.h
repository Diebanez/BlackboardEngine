//
// Created by diego on 24/07/2020.
//

#ifndef BLACKBOARDENGINE_INPUT_H
#define BLACKBOARDENGINE_INPUT_H

namespace BlackboardRuntime {
    class Input {
    public:
        inline static bool IsKeyPressed(int keycode) { return m_Instance->IsKeyPressedImpl(keycode); }
        inline static bool IsKeyDown(int keycode) { return m_Instance->IsKeyDownImpl(keycode); }
        inline static bool IsKeyUp(int keycode) { return m_Instance->IsKeyUpImpl(keycode); }

        inline static bool IsMouseButtonPressed(int button) { return m_Instance->IsMouseButtonPressedImpl(button); };
        inline static bool IsMouseButtonDown(int button) { return m_Instance->IsMouseButtonDownImpl(button); };
        inline static bool IsMouseButtonUp(int button) { return m_Instance->IsMouseButtonUpImpl(button); };
        inline static std::pair<float, float> GetMousePosition() { return m_Instance->GetMousePositionImpl(); };
    protected:
        virtual bool IsKeyPressedImpl(int keycode) = 0;
        virtual bool IsKeyDownImpl(int keycode) = 0;
        virtual bool IsKeyUpImpl(int keycode) = 0;

        virtual bool IsMouseButtonPressedImpl(int button) = 0;
        virtual bool IsMouseButtonDownImpl(int button) = 0;
        virtual bool IsMouseButtonUpImpl(int button) = 0;
        virtual std::pair<float, float> GetMousePositionImpl() = 0;

    private:
        static Input *m_Instance;
    };
}

#endif //BLACKBOARDENGINE_INPUT_H
