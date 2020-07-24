#pragma once
#include <Input/Input.h>

namespace BlackboardRuntime {
	class WindowsInput : public Input {
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