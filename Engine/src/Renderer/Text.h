#pragma once
#include "Engine.h"

struct SDL_Texture;

namespace pb {
	class Font;
	class Renderer;
	struct Color;
	struct Vector2;
	
	// !! forward declare the Font, Renderer, Color and Vector2 classes 
	class Text
	{
	public:
		//<!!create default constructor>
		Text(Font* font) : m_font{ font } {}//
		~Text();

		void Create(Renderer& renderer, const std::string& text, const Color& color);
		void Draw(Renderer& renderer, const Vector2& position);

		friend class Font;
		friend class Renderer;

	private:
		Font* m_font {nullptr}; //<!!initialize m_font to nullptr>
		SDL_Texture* m_texture {nullptr}; //<!!initialize m_texture to nullptr>
	};
}