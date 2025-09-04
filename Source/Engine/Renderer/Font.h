#pragma once
#include "Resources/Resource.h"
#include <SDL3/SDL_ttf.h>
#include <string>

namespace nebula {

	class Font : public Resource{
	public:
		Font() = default;
		~Font();

		bool Load(const std::string& name, float fontSize);

	private:
		friend class Text;

		TTF_Font* m_ttfFont{ nullptr }; 
	};

}