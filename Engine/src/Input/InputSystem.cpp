#include "InputSystem.h"
#include <iostream>
#include <SDL.h>

namespace pb {

	const uint32_t M_key_left = 0;
	const uint32_t M_key_middle = 1;
	const uint32_t M_key_right = 2;

	const uint32_t C_key_space = SDL_SCANCODE_SPACE;
	const uint32_t C_key_up = SDL_SCANCODE_UP;
	const uint32_t C_key_down = SDL_SCANCODE_DOWN;
	const uint32_t C_key_left = SDL_SCANCODE_LEFT;
	const uint32_t C_key_right = SDL_SCANCODE_RIGHT;
	const uint32_t C_key_escape = SDL_SCANCODE_ESCAPE;



	InputSystem::KeyState InputSystem::GetButtonState(uint32_t button)
	{
		KeyState keyState = KeyState::IDLE;

		bool buttonDown = GetButtonDown(button);
		bool prevButtonDown = GetPreviousButtonDown(button);

		// set the keyState if buttonDown (true) and prevButtonDown (true) 
		// fill in the remaining states 

		return keyState;
	}

	void InputSystem::Initialize()
	{
		const uint8_t* keyboardstate = SDL_GetKeyboardState(&m_numKeys);

		m_keyboardState.resize(m_numKeys);
		std::copy(keyboardstate, keyboardstate + m_numKeys, m_keyboardState.begin());

		m_prevKeyboardState
			= m_keyboardState;
	}
	void InputSystem::Shutdown()
	{

	}
	void InputSystem::Update()
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		//save prev keyboard state
		m_prevKeyboardState
			= m_keyboardState;

		//get current keyboard state
		const uint8_t* keyboardstate = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardstate, keyboardstate + m_numKeys, m_keyboardState.begin());

		m_prevMouseButtonState = m_mouseButtonState;
		int x, y;
		uint32_t buttons = SDL_GetMouseState(&x, &y);
		m_mousePosition = pb::Vector2{ x , y };
		m_mouseButtonState[0] = buttons & SDL_BUTTON_LMASK; // buttons [0001] & [0RML] 
		m_mouseButtonState[1] = buttons & SDL_BUTTON_MMASK; // buttons [0010] & [0RML] 
		m_mouseButtonState[2] = buttons & SDL_BUTTON_RMASK; // buttons [0100] & [0RML] 
		//std::cout << GetMousePosition().x << " " << GetMousePosition().y << std::endl;
	}
	InputSystem::KeyState InputSystem::GetKeyState(uint32_t key)
	{
		bool keyDown = GetKeyDown(key);
		bool prevKeyDown = GetPreviousKeyDown(key);
		if (keyDown) {
			if (prevKeyDown) {
				return InputSystem::KeyState::HELD;
			}
			else {
				return InputSystem::KeyState::PRESSED;
			}
		}
		else {
			if (prevKeyDown) {
				return InputSystem::KeyState::RELEASED;
			}
			else {
				return InputSystem::KeyState::IDLE;
			}
		}
		
	}
}