#include "AudioClip.h"
#include "Audio System.h"

namespace viper {
	AudioClip::~AudioClip()
	{
		if (m_sound) m_sound->release();
	}

	bool AudioClip::Load(const std::string& key, AudioSystem& audioSystem)
	{
		FMOD_RESULT result = audioSystem.m_system->createSound(key.c_str(), FMOD_DEFAULT, 0, &m_sound);
		if (!AudioSystem::checkFMODResult(result)) return false;
		return true;
	}
}
