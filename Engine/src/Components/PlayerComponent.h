#pragma once
#include "Framework/Component.h"
#include "Physics/Collision.h"
#include "CharacterComponent.h"

namespace pb
{
	class Actor;

	class PlayerComponent : public CharacterComponent
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
		virtual void OnNotify(const Event& event) override;

	public:
		float jump = 60;
		int grounded = 0;

		Vector2 m_checkpoint;
	};
}