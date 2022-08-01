#pragma once
#include "../Math/Vector2.h"
#include <cstdint>
#include <vector>
#include <array>

namespace pb {
	class InputSystem {
	public:

		enum KeyState
		{
			IDLE,
			PRESSED,
			HELD,
			RELEASED
		};

		const pb::Vector2& GetMousePosition() const { return m_mousePosition; }


		KeyState GetButtonState(uint32_t button);
		bool GetButtonDown(uint32_t button) { return m_mouseButtonState[button]; }
		bool GetPreviousButtonDown(uint32_t button) {
			return m_prevMouseButtonState[button];
		}

		InputSystem() = default;
		~InputSystem() = default;

		void Initialize();
		void Shutdown();

		void Update();

		KeyState GetKeyState(uint32_t key);

		bool GetKeyDown(uint32_t button) { return m_keyboardState[button]; }
		bool GetPreviousKeyDown(uint32_t button) {
			return m_prevKeyboardState[button];
		}

	private:
		int m_numKeys;

		std::vector<uint8_t> m_keyboardState;
		std::vector<uint8_t> m_prevKeyboardState;


		pb::Vector2 m_mousePosition;
		std::array<uint8_t, 3> m_mouseButtonState;
		std::array<uint8_t, 3> m_prevMouseButtonState;


	};

	extern const uint32_t M_key_left;
	extern const uint32_t M_key_middle;
	extern const uint32_t M_key_right;

	extern const uint32_t C_key_space;
	extern const uint32_t C_key_up;
	extern const uint32_t C_key_down;
	extern const uint32_t C_key_left;
	extern const uint32_t C_key_right;
	extern const uint32_t C_key_escape;
	
}

