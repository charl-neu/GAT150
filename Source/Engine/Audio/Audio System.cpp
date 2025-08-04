#include "Audio System.h"
#include <iostream>
#include <fmod_errors.h>

namespace viper {
	/// <summary>
	/// Checks the FMOD result and prints an error message if the result is not OK.
	/// </summary>
	/// <param name="result"></param>
	/// <returns> retruns true if the result is OK, false otherwise. </returns> 
	bool AudioSystem::checkFMODResult(FMOD_RESULT result) {
		if (result != FMOD_OK) {
			std::cerr << FMOD_ErrorString(result) << std::endl;
			return false;
		}
		return true;
	}

	/// <summary>
	/// Initializes the audio system.
	/// </summary>
	/// <returns>true if successful, false otherwise.</returns> 
	bool AudioSystem::Initialize() {
		FMOD_RESULT result = FMOD::System_Create(&m_system);

		if (!checkFMODResult(result)) return false;

		void* extradriverdata = nullptr;
		m_system->init(32, FMOD_INIT_NORMAL, extradriverdata);
		if (!checkFMODResult(result)) return false;

		return true;
	}

	/// <summary>
	/// Shuts down the audio system and releases associated resources.
	/// </summary>
	void AudioSystem::Shutdown() {
		FMOD_RESULT result = m_system->release();;
		checkFMODResult(result);
	}

	/// <summary>
	/// Updates the audio system if it is initialized.
	/// </summary>
	void AudioSystem::Update() {
		if (m_system) {
			m_system->update();
		}
	}

	/// <summary>
	/// Attempts to add a new sound to the audio system using the specified filename and name.
	/// </summary>
	/// <param name="filename">The path to the sound file to be loaded.</param>
	/// <param name="name">The name to associate with the sound. If empty, the filename is used as the key.</param>
	/// <returns>Returns false if the sound could not be added (e.g., if a sound with the same name already exists or loading fails).</returns>
	bool viper::AudioSystem::AddSound(const std::string& filename, const std::string& name)
	{
		std::string key = name.empty() ? filename : name;

		key = toLower(key); //convert key to lowercase

		//check if key exists in sounds map
		if (m_sounds.find(key) != m_sounds.end()) {
			std::cerr << "Sound with name '" << key << "' already exists." << std::endl;
			return false;
		}

		FMOD::Sound* sound = nullptr;
		FMOD_RESULT result = m_system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
		if (!checkFMODResult(result)) return false;

		//insert sound into the map
		m_sounds[key] = sound;

		return true;
	}

	bool viper::AudioSystem::PlaySound(const std::string& name)
	{
		std::string key = name;
		for (char c : key) {
			c = std::tolower(c);
		}

		if (m_sounds.find(key) == m_sounds.end()) {
			std::cerr << "Sound with name '" << key << "' does not exist." << std::endl;
			return false;
		}


		m_system->playSound(m_sounds[name], 0, false, nullptr);

		return true;
	}

} // namespace viper

