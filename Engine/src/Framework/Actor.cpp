#include "Actor.h"
#include "Components/RenderComponent.h"
#include "Factory.h"

namespace pb {
	Actor::Actor(const Actor& other)
	{
		name = other.name;
		tag = other.tag;
		m_transform = other.m_transform;

		m_scene = other.m_scene;

		for (auto& component : other.m_components) {
			auto clone = std::unique_ptr<Component>((Component*)component->Clone().release());
			AddComponent(std::move(clone));
		}
	}
	void Actor::Update()
	{
		if (!active) {
			for (auto& component : m_components)
			{
				component->Update();
			}
		}
	}
	void Actor::Draw(Renderer& renderer)
	{
		if (!active) {
			for (auto& component : m_components)
			{
				auto renderComponent = dynamic_cast<RenderComponent*>(component.get());
				if (renderComponent)
				{
					renderComponent->Draw(renderer);
				}
			}
		}
	}

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		
		m_components.push_back(std::move(component));
	}

	bool Actor::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool Actor::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, tag);
		READ_DATA(value, name);
		READ_DATA(value, active);

		if (value.HasMember("transform")) m_transform.Read(value["transform"]);
		if (value.HasMember("components") && value["components"].IsArray()) {
			for (auto& compValue : value["components"].GetArray()) {

				std::string type;
				READ_DATA(compValue, type);
				std::cout << type << std::endl;
				auto component = Factory::Instance().Create<Component>(type);
				if (component) {
					component->Read(compValue);
					
					AddComponent(std::move(component));
				}
			}
		}
		return true;
	}

	void Actor::Initialize()
	{
		std::cout << this->GetName() << std::endl;
		for (auto& component : m_components) {
			component->Initialize();
		}
		for (auto& child : m_children) {
			child->Initialize();
		}
	}

	std::unique_ptr<GameObject> Actor::Clone()
	{
		return std::unique_ptr<GameObject>();
	}

	
}