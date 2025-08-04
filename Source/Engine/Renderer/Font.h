#pragma once
#include <SDL3/SDL_ttf.h>
#include <string>

namespace viper {

	class Font {
	public:
		Font() = default;
		~Font();

		bool Load(const std::string& name, float fontSize);

	private:
		friend class Text;

		TTF_Font* m_ttfFont{ nullptr }; 
	};

}