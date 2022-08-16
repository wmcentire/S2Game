#pragma once
#include "Framework/Component.h"

namespace pb
{
	class PlayerComponent : public Component
	{
	public:
		PlayerComponent() = default;

		void Update() override;

	private:

		pb::Vector2 m_velocity;

		float m_maxSpeedX{ 250 };
		float m_gravity{ 50 };
		float m_speedX{ 0 };
		float m_speedY{ 0 };
		float m_drag{ 1.0f };
		float m_health{ 10 };
		
	};
}