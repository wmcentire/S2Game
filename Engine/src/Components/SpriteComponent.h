#pragma once
#include "RenderComponent.h"
namespace pb
{
	class Texture;

	class SpriteComponent : public RenderComponent
	{
	public:
		// Inherited via RenderComponent
		virtual void Update() override;
		virtual void Draw(Renderer& renderer) override;

	public:
		std::shared_ptr<Texture> m_texture;


	protected:

	};
}