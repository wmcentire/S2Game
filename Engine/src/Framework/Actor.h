#pragma once
#include "Framework/GameObject.h"
#include "Renderer/Model.h"

namespace pb {

	class Scene;

	class Actor : public GameObject {
	public:
		Actor() = default;
		Actor(const Model& modelIn,const Transform& transformIn) :
			GameObject{transformIn}
			,m_model{modelIn} {}

		virtual void Update() override {}
		virtual void Draw(Renderer& renderer);

		friend class Scene;

		virtual void OnCollision(Actor* collided) {}

		float GetRadius() { return m_model.GetRadius() * m_transform.scale; }
		std::string& GetTag() { return m_tag; }

	protected:
		std::string m_tag;

		bool m_destroy = false;
		Vector2 m_velocity;
		float m_damping = 1;

		Scene* m_scene = nullptr;
		Model m_model;
	};

}