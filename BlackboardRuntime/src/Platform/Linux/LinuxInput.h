//
// Created by diego on 05/08/2020.
//
#ifdef BB_LINUX_PLATFORM
#ifndef BLACKBOARDENGINE_LINUXINPUT_H
#define BLACKBOARDENGINE_LINUXINPUT_H

#include <Input/Input.h>

namespace BlackboardRuntime {

    class LinuxInput : public Input {
    protected:
        bool IsKeyPressedImpl(int keycode) override;
        bool IsKeyDownImpl(int keycode) override;
        bool IsKeyUpImpl(int keycode) override;


        bool IsMouseButtonPressedImpl(int button) override;
        bool IsMouseButtonDownImpl(int button) override;
        bool IsMouseButtonUpImpl(int button) override;

        std::pair<float, float> GetMousePositionImpl() override;
    };

}
#endif //BLACKBOARDENGINE_LINUXINPUT_H
#endif