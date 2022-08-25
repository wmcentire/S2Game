#pragma once
#include "Framework/Component.h"
#include "Physics/Collision.h"

namespace pb
{
	class PlayerComponent : public Component, public ICollision
	{
	public:
		PlayerComponent() = default;
		CLASS_DECLARATION(PlayerComponent)
		void Initialize() override;
		void Update() override;
		
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		virtual void OnCollisionEnter(Actor* other) override;
		virtual void OnCollisionExit(Actor* other) override;

	public:
		float speed = 0;
	};
}