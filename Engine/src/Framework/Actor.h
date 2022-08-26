#pragma once
#include "Framework/GameObject.h"
#include "Renderer/Model.h"
#include "Framework/Component.h"

namespace pb {

	class Scene;

	class Actor : public GameObject, public ISerializable {
	public:
		Actor() = default;
		Actor(const Actor& other);
		Actor(const Transform& transformIn) :
			GameObject{transformIn}
			 {}

		//CLASS_DECLARATION(Actor)

		virtual void Update() override;
		virtual void Draw(Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);

		friend class Scene;
		friend class Component;

		template<typename T>
		T* GetComponent();

		virtual void OnCollision(Actor* collided) {}

		void SetDestroy() { m_destroy = true; }

		void SetActive(bool active = true) { active = active; }

		float GetRadius() { return m_model.GetRadius() * std::max(m_transform.scale.x, m_transform.scale.y); }
		const std::string& GetTag() { return tag; }
		void SetTag(const std::string& tag) { this->tag = tag; }

		const std::string& GetName() { return name; }
		void SetName(const std::string& name) { this->name = name; }
		
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
		
		virtual void Initialize() override;
		virtual std::unique_ptr<GameObject> Clone() override;

		bool IsActive() { return active; }

	protected:
		std::string name;
		std::string tag;

		bool active = true;
		bool m_destroy = false;
		

		Scene* m_scene = nullptr;
		Model m_model;

		std::vector<std::unique_ptr<Component>> m_components;
		std::vector<std::unique_ptr<Actor>> m_children;




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