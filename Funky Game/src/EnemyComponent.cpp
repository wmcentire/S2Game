#include "EnemyComponent.h"
#include "Engine.h"
#include <iostream>

void EnemyComponent::Initialize()
{
    CharacterComponent::Initialize();
}

void EnemyComponent::Update()
{
    auto actor = m_owner->GetScene()->GetActorFromName("Player");
    if (actor)
    {
        pb::Vector2 direction = actor->m_transform.position - m_owner->m_transform.position;
        pb::Vector2 force = direction.Normalized() * speed;

        auto component = m_owner->GetComponent<pb::PhysicsComponent>();
        if (component) component->ApplyForce(force);
    }
}

void EnemyComponent::OnCollisionEnter(pb::Actor* other)
{
    if (other->GetName() == "Player")
    {
        pb::Event event;
        event.name = "EVENT_DAMAGE";
        event.data = damage;
        event.reciever = other;
        pb::g_eventManager.Notify({"EVENT_DAMAGE",other,damage});
    }
}

void EnemyComponent::OnCollisionExit(pb::Actor* other)
{
}

void EnemyComponent::OnNotify(const pb::Event& event)
{
    if (event.name == "EVENT_DAMAGE") {
        health -= std::get<float>(event.data);
        std::cout << health << std::endl;
        if (health <= 0) {
            m_owner->SetDestroy();
        }
    }

}

bool EnemyComponent::Write(const rapidjson::Value& value) const
{
    return true;
}

bool EnemyComponent::Read(const rapidjson::Value& value)
{
    CharacterComponent::Read(value);

    return true;
}