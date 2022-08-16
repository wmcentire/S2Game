#pragma once
#include "Framework/GameObject.h"
#include "Renderer/Model.h"
#include "Framework/Component.h"

namespace pb {

	class Scene;

	class Actor : public GameObject {
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
		std::string& GetTag() { return m_tag; }

	protected:
		std::string m_tag;

		bool m_destroy = false;
		Vector2 m_velocity;
		float m_damping = 1;

		Scene* m_scene = nullptr;
		Model m_model;

		std::vector<std::unique_ptr<Component>> m_components;

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