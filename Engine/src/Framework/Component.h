#pragma once
#include "Framework/GameObject.h"


namespace pb
{
	class Actor;
	class Component : public GameObject
	{
	public:
		Component() = default;

		virtual void Update() = 0;

		friend class Actor;
	protected:
		Actor* m_owner = nullptr;


	};
}