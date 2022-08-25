#pragma once
#include "Math/Transform.h"
#include "Serialization/Serializable.h"
#include <memory>

#define CLASS_DECLARATION(class) std::unique_ptr<GameObject> Clone() override { return std::make_unique<class>(*this); }
#define REGISTER_CLASS(class) Factory::Instance().Register<class>(#class);

namespace pb {

	class GameObject {
	public:
		GameObject() = default;
		GameObject(const Transform& transformIn) : m_transform{transformIn}{}

		virtual void Update() = 0;
		virtual void Initialize() = 0;
		virtual std::unique_ptr<GameObject> Clone() = 0;

		Transform m_transform;
	protected:

	};
}