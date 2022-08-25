#pragma once
#include "Framework/GameObject.h"
#include "Renderer/Model.h"
#include "Framework/Component.h"

namespace pb {

	class Scene;

	class Actor : public GameObject, public ISerializable {
	public:
		Actor() = default;
		Actor(const Transform& transformIn) :
			GameObject{transformIn}
			 {}

		virtual void Update() override;
		virtual void Draw(Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);

		friend class Scene;
		friend class Component;

		template<typename T>
		T* GetComponent();

		virtual void OnCollision(Actor* collided) {}

		float GetRadius() { return m_model.GetRadius() * std::max(m_transform.scale.x, m_transform.scale.y); }
		const std::string& GetTag() { return tag; }
		void SetTag(const std::string& tag) { this->tag = tag; }

		const std::string& GetName() { return name; }
		void SetName(const std::string& name) { this->name = name; }
		
		// Inherited via ISerializable
		virtual bool Write(const rapidjson::Value& value) const override;

		virtual bool Read(const rapidjson::Value& value) override;

	protected:
		std::string name;
		std::string tag;


		bool m_destroy = false;
		Vector2 m_velocity;
		float m_damping = 1;

		Scene* m_scene = nullptr;
		Model m_model;

		std::vector<std::unique_ptr<Component>> m_components;
		std::vector<std::unique_ptr<Actor>> m_children;



		// Inherited via GameObject
		virtual void Initialize() override;

	};
	template<typename T>
	inline T* Actor::GetComponent() {
		for (auto& component : m_components) {
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}
		return nullptr;
	}
}