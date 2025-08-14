#include "AudioSource.h"
#include "Audio/AudioClip.h"
#include "Engine.h"


namespace viper {
	void AudioSource::Update(float deltaTime)
	{

	}

	void AudioSource::Play()
	{
		auto audio = Resources().Get<AudioClip>(audioClipName, GetEngine().GetAudioSystem());
		if (audio) {
			GetEngine().GetAudioSystem().PlaySound(*audio);
		}
	}
}