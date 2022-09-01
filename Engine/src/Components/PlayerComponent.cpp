#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>

namespace pb
{
	void PlayerComponent::Initialize()
	{
		CharacterComponent::Initialize();
		g_eventManager.Subscribe("EVENT_CHECKPOINT", std::bind(&CharacterComponent::OnNotify, this, std::placeholders::_1), m_owner);


	}
	void PlayerComponent::Update()
	{
		float jumpLimit = 0;
		//button checks
			// - movement
		float thrust = 0;
		
		pb::Vector2 direction{ 0,0 };
		if (g_inputSystem.GetKeyState(C_key_w) == pb::InputSystem::HELD) {
			
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
			auto component = m_owner->GetComponent<PhysicsComponent>();
			if (component)
			{
				if (grounded) {
					jumpLimit += 1 * g_time.deltaTime;
					//create a jump cap
 					if (jumpLimit < 800) {
						component->ApplyForce(Vector2::up * jump);
					}
				}
			}
			
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

		// set camera 
		auto camera = m_owner->GetScene()->GetActorFromName("Camera");
		if (camera)
		{
			camera->m_transform.position = pb::Lerp(camera -> m_transform.position, m_owner->m_transform.position, 2 * g_time.deltaTime);
		}
	}
	bool PlayerComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool PlayerComponent::Read(const rapidjson::Value& value)
	{
		CharacterComponent::Read(value);
		READ_DATA(value, jump);
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
		if (other->GetTag() == "Ground") {
			grounded++;			
		}
		if (other->GetTag() == "Wasp") {
			Event _event;
			_event.name = "EVENT_DAMAGE";
			_event.data = damage;
			_event.reciever = other;

			g_eventManager.Notify(_event);
			other->SetDestroy();
		}
	}
	void PlayerComponent::OnCollisionExit(Actor* other)
	{
		if (other->GetTag() == "Ground") {
			grounded--;
		}
	}
	void PlayerComponent::OnNotify(const Event& event)
	{
		if (event.name == "EVENT_DAMAGE") {
			health -= std::get<float>(event.data);
			if (health <= 0) {
				//respawn at checkpoint
				health = 3;
			}
		}
		if (event.name == "EVENT_CHECKPOINT") {
			m_checkpoint = std::get<Vector2>(event.data);
		}
	}
}