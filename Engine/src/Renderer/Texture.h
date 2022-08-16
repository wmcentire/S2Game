#pragma once
#include "Math\Vector2.h" 
#include "Resources/Resource.h"
#include <string> 

// !! forward declaration for SDL pointers below (SDL likes to use structs) 
struct SDL_Texture;
// !! add namespace 
namespace pb{
// !! forward declaration for Renderer below 
	class Renderer;
	class Texture : public Resource{
	public:
		Texture() = default;
		~Texture();

		bool Create(std::string filename, ...) override;

		bool Create(Renderer& renderer, const std::string& filename);

		Vector2 GetSize() const;

	// !! allow Renderer to access private texture data (friend) 
		friend class Renderer;
	private:
		SDL_Texture* m_texture = nullptr;
};
}