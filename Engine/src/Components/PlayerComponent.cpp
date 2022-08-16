#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>

namespace pb
{
	void PlayerComponent::Update()
	{
		
		//button checks
			// - movement
		float thrust = 0;
		
		pb::Vector2 direction{ 0,0 };
		if (g_inputSystem.GetKeyState(C_key_w) == pb::InputSystem::HELD) {
			thrust = 500;
		}
		if (g_inputSystem.GetKeyState(C_key_a) == pb::InputSystem::HELD) {
			m_owner->m_transform.rotation -= 180 * pb::g_time.deltaTime;
		}
		if (g_inputSystem.GetKeyState(C_key_s) == pb::InputSystem::HELD) {
			//dash downwards
			thrust = -500;
		}
		if (g_inputSystem.GetKeyState(C_key_d) == pb::InputSystem::HELD) {
			m_owner->m_transform.rotation += 180 * pb::g_time.deltaTime;
		}
		if (g_inputSystem.GetKeyState(C_key_space) == pb::InputSystem::PRESSED) {

			auto component = m_owner->GetComponent<AudioComponent>();
			if (component)
			{
				component->PlaySound();
			}
		}
			// - firing
		if (g_inputSystem.GetKeyState(C_key_left) == pb::InputSystem::PRESSED) {
			//implement shooting bullet
			std::cout << "leftpressed \n";
			auto component = m_owner->GetComponent<AudioComponent>();
			if (component) {
				component->PlaySound();
			}
			
		}
		if (g_inputSystem.GetKeyState(C_key_right) == pb::InputSystem::PRESSED) {
			//implement shooting bullet
			auto component = m_owner->GetComponent<AudioComponent>();
			if (component) {
				component->PlaySound();
			}
		}

		auto componentT =  m_owner->GetComponent<PhysicsComponent>();
		if (componentT) {
			//thrust
			Vector2 force = Vector2::Rotate({1,0},m_owner->m_transform.rotation) * thrust;
			componentT->ApplyForce(force);

			//gravity
			force = (Vector2{ 300,300 } - m_owner->m_transform.position).Normalized() * 100.0f;
			componentT->ApplyForce(force);
		}

		

		m_owner->m_transform.position += direction * 300 * pb::g_time.deltaTime;
	}
}