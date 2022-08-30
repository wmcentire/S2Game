#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>

namespace pb
{
	void PlayerComponent::Initialize()
	{
		auto component = m_owner->GetComponent<CollisionComponent>();
		if (component) {
			component->SetCollisionEnter(std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1));
			component->SetCollisionExit(std::bind(&PlayerComponent::OnCollisionExit, this, std::placeholders::_1));
		}
	}
	void PlayerComponent::Update()
	{
		float jumpLimit = 0;
		//button checks
			// - movement
		float thrust = 0;
		
		pb::Vector2 direction{ 0,0 };
		if (g_inputSystem.GetKeyState(C_key_w) == pb::InputSystem::HELD) {
			auto component = m_owner->GetComponent<PhysicsComponent>();
			if (component)
			{
				jumpLimit += 1 * g_time.deltaTime;
				//create a jump cap
				if (jumpLimit < 800) {
					component->ApplyForce(Vector2::up * speed);
				}
			}
		}
		//resets the jump limit counter
		if (g_inputSystem.GetKeyState(C_key_w) == pb::InputSystem::HELD) {
			jumpLimit = 0;
		}
		if (g_inputSystem.GetKeyState(C_key_a) == pb::InputSystem::HELD) {
			direction = Vector2::left;
		}
		if (g_inputSystem.GetKeyState(C_key_s) == pb::InputSystem::HELD) {
			//dash downwards
			thrust = -speed;
		}
		if (g_inputSystem.GetKeyState(C_key_d) == pb::InputSystem::HELD) {
			direction = Vector2::right;
		}
		if (g_inputSystem.GetKeyState(C_key_space) == pb::InputSystem::PRESSED) {

			
		}



			// - firing
		if (g_inputSystem.GetKeyState(C_key_left) == pb::InputSystem::PRESSED) {
			//implement shooting bullet
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

		Vector2 velocity;

		auto component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			component->ApplyForce(direction * speed);
			velocity = component->m_velocity;
		}

		auto renderComponent = m_owner->GetComponent<RenderComponent>();
		if (renderComponent) {
			if (velocity != 0) {
				renderComponent->SetFlipHorizontal(velocity.x > 0);
			}
		}

		//m_owner->m_transform.position += direction * 300 * g_time.deltaTime;
	}
	bool PlayerComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool PlayerComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, speed);
		return true;
	}
	void PlayerComponent::OnCollisionEnter(Actor* other)
	{
		if (other->GetName() == "Coin") {
			Event _event;
			_event.name = "EVENT_ADD_POINTS";
			_event.data = 100;

			g_eventManager.Notify(_event);
			other->SetDestroy();
		}
	}
	void PlayerComponent::OnCollisionExit(Actor* other)
	{

	}
}