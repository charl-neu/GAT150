#pragma once
#include "Game/Component.h"
#include <string>

namespace viper {
	class AudioSource : public Component
	{
	public:
		std::string audioClipName;

	private:
		void Play();
		void Update(float deltaTime);
	};
}