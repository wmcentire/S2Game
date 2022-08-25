#pragma once
#include "PhysicsComponent.h"
#include "Physics/PhysicsSystem.h"

namespace pb {
	class RBPhysicsComponent : public PhysicsComponent {
	public:
		RBPhysicsComponent() = default;
		~RBPhysicsComponent();
		CLASS_DECLARATION(RBPhysicsComponent)
		virtual void ApplyForce(const Vector2& force) override;
		void Update() override;
		virtual void Initialize() override;

	public:
		Vector2 m_velocity;
		Vector2 m_acceleration;

		float m_damping = .75f;

		// Inherited via Component
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		friend class CollisionComponent;

	private:
		pb::RigidBodyData data;
		b2Body* m_body = nullptr;
	};
}