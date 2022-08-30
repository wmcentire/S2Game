#include "CollisionComponent.h"
#include "RBPhysicsComponent.h"
#include "Engine.h"

namespace pb {

    bool CollisionComponent::Write(const rapidjson::Value& value) const
    {
        return true;
    }

    bool pb::CollisionComponent::Read(const rapidjson::Value& value)
    {

        READ_DATA(value, data.size);
        READ_DATA(value, data.density);
        READ_DATA(value, data.friction);
        READ_DATA(value, data.restitution);
        READ_DATA(value, data.is_trigger);
        return true;
    }

    void CollisionComponent::Update()
    {

    }

    void CollisionComponent::Initialize()
    {
        auto component = m_owner->GetComponent<RBPhysicsComponent>();
        if (component)
        {
            // if data was not set, get size from render component source rect 
            if (data.size.x == 0 && data.size.y == 0) 
                {
                auto renderComponent = m_owner->GetComponent<RenderComponent>(); // !! check render component from the owner 
                    if (renderComponent)
                    {
                        data.size = Vector2{ renderComponent->GetSource().w, renderComponent->GetSource().h};
                    }
                }

            g_physicssystem.SetCollisionBox(component->m_body, data, m_owner);
        }
    }

    void CollisionComponent::OnCollisionEnter(Actor* other)
    {
        if(m_enterFunction) m_enterFunction(other);
    }

    void CollisionComponent::OnCollisionExit(Actor* other)
    {
        if (m_exitFunction) m_exitFunction(other);

    }
}