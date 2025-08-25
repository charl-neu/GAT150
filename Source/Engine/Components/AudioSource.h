#pragma once
#include "Game/Component.h"
#include <string>

namespace viper {
	
	class AudioSource : public Component
	{
	public:
		std::string audioClipName;

	public:
		CLASS_PROTOTYPE(AudioSource)

		void Update(float deltaTime) override;
		void Play();
	};
}