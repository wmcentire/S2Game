#include "Actor.h"
#include "Components/RenderComponent.h"
#include "Factory.h"

namespace pb {

	void Actor::Update()
	{
		for (auto& component : m_components)
		{
			component->Update();
		}
	}
	void Actor::Draw(Renderer& renderer)
	{
		for (auto& component : m_components)
		{
			auto renderComponent = dynamic_cast<RenderComponent*>(component.get());
			if (renderComponent)
			{
				renderComponent->Draw(renderer);
			}
			//component->Update();
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

		if (value.HasMember("transform")) m_transform.Read(value["transform"]);
		if (value.HasMember("components") && value["components"].IsArray()) {
			for (auto& compValue : value["components"].GetArray()) {

				std::string type;
				READ_DATA(compValue, type);

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
		for (auto& component : m_components) {
			component->Initialize();
		}
		for (auto& child : m_children) {
			child->Initialize();
		}
	}

	
}