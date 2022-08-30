#pragma once
#include "Framework/Component.h"
#include "Math/Rect.h"
#include "Math/Vector2.h"
namespace pb
{
	class Renderer;

	class RenderComponent : public Component
	{
	public:
		virtual void Draw(Renderer& renderer) = 0;
		void SetFlipHorizontal(bool flip = true) { flipHorizontal = flip; }
		bool GetFlipHorizontal() { return flipHorizontal; }
		virtual Rect& GetSource() { return source; }
	protected:
		bool flipHorizontal = false;
		Rect source;
		Vector2 registration = Vector2{ 0.5f, 0.5f };
	};
}