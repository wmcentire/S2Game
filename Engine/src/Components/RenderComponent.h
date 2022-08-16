#pragma once
#include "Framework/Component.h"
namespace pb
{
	class Renderer;

	class RenderComponent : public Component
	{
	public:
		virtual void Draw(Renderer& renderer) = 0;
	};
}