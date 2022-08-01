#pragma once
#include "Math/Transform.h"
#include "Math/Vector2.h"

namespace pb {

	class GameObject {
	public:
		GameObject() = default;
		GameObject(const Transform& transformIn) : m_transform{transformIn}{}

		virtual void Update() = 0;

		Transform m_transform;
	protected:

	};
}