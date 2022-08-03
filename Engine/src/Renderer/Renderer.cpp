#include "Renderer.h" 
#include "Texture.h"
#include <SDL.h>
#include <SDL_ttf.h> 
#include <SDL_image.h>

namespace pb
{
	SDL_Renderer* renderer{ nullptr };
	SDL_Window* window{ nullptr };

	void CreateWindow(int width, int height)
	{
		//initialize
		window = SDL_CreateWindow("Game", 100, 100, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		renderer = SDL_CreateRenderer(window, -
			1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	}
	void Renderer::Initialize()
	{
		SDL_Init(SDL_INIT_VIDEO);
		TTF_Init();
	}

	void Renderer::Shutdown()
	{
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		TTF_Quit();
	}

	void Renderer::CreateWindow(const char* name, int width, int height)
	{
		m_width = width;
		m_height = height;
		m_window = SDL_CreateWindow(name, 100, 100, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	}

	void Renderer::BeginFrame()
	{
		SDL_SetRenderDrawColor(m_renderer, m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
		SDL_RenderClear(m_renderer);
	}

	void Renderer::EndFrame()
	{
		SDL_RenderPresent(m_renderer);
	}
	void Renderer::SetClearColor(pb::Color colorClear)
	{

	}
	void Renderer::DrawLine(float x1, float y1, float x2, float y2)
	{

		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		SDL_RenderDrawLineF(m_renderer, x1, y1, x2, y2);
	}
	void Renderer::DrawLine(const Vector2& v1, const Vector2& v2, const Color& color)
	{
		SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLineF(m_renderer, v1.x, v1.y, v2.x, v2.y);

	}

	void Renderer::DrawPoint(const Vector2& v, const Color& color)
	{
		SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawPointF(m_renderer, v.x, v.y);
	}

	void Renderer::DrawPoint(float x, float y)
	{
		SDL_RenderDrawPointF(m_renderer, x, y);
	}
	void Renderer::Draw(std::shared_ptr<Texture> texture, const Vector2& position, float angle)
	{
		Vector2 size = texture->GetSize();

		SDL_Rect dest;
		// !! make sure to cast to int to prevent compiler warnings 
		dest.x = position.x;// !! set to position x 
		dest.y = position.y;// !! set to position y 
		dest.w = size.x;// !! set to size x 
		dest.h = size.y;// !! set to size y 

		SDL_RenderCopyEx(m_renderer, texture -> m_texture, nullptr, &dest, angle, nullptr, SDL_FLIP_NONE);
	}
	
}
