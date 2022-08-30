#include "RBPhysicsComponent.h"
#include "Engine.h"

namespace pb {
	RBPhysicsComponent::~RBPhysicsComponent()
	{

	}
	void RBPhysicsComponent::ApplyForce(const Vector2& force)
	{
		b2Vec2 v{ force.x,force.y };
		m_body->ApplyForceToCenter(v, true);

	}
	void RBPhysicsComponent::Update()
	{
		Vector2 position = B2VEC2_TO_VECTOR2(m_body->GetPosition());
		m_owner->m_transform.position = PhysicsSystem::WorldToScreen(position);
		m_owner->m_transform.rotation = m_body->GetAngle();

		m_velocity = B2VEC2_TO_VECTOR2(m_body->GetLinearVelocity());
	}

	void RBPhysicsComponent::Initialize()
	{
		m_body = g_physicssystem.CreateBody(m_owner->m_transform.position, m_owner->m_transform.rotation, data);
		m_body->SetGravityScale(data.gravity_scale);
		m_body->SetLinearDamping(damping);
	}
	bool RBPhysicsComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}
	bool RBPhysicsComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, data.gravity_scale);
		READ_DATA(value, data.constraint_angle);
		READ_DATA(value, data.is_dynamic);
		return true;
	}
}
