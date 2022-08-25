#pragma once
#include "Math/Transform.h"
#include "Serialization/Serializable.h"

#define REGISTER_CLASS(class) Factory::Instance().Register<class>(#class);

namespace pb {

	class GameObject {
	public:
		GameObject() = default;
		GameObject(const Transform& transformIn) : m_transform{transformIn}{}

		virtual void Update() = 0;
		virtual void Initialize() = 0;

		Transform m_transform;
	protected:

	};
}