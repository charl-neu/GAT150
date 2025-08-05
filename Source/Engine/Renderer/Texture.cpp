#include "Texture.h"
#include "Renderer.h"
#include "Math/Vector2.h"
#include <SDL3_image/SDL_image.h>

namespace viper {
	Texture::~Texture() {
		if (m_texture) {
			SDL_DestroyTexture(m_texture);
			m_texture = nullptr;
		}
	}

	bool Texture::Load(const std::string& filename, Renderer& renderer) {


		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (!surface) {
			std::cerr << "Failed to load image: " << filename << std::endl;
			return false;
		}


		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		if (!m_texture) {
			std::cerr << "Failed to load texture: " << filename << std::endl;
			return false;
		}
		return true;

	}

	vec2 Texture::GetSize() {
		float w, h;
		SDL_GetTextureSize(m_texture, &w, &h);

		return vec2{ w, h };
	}
}