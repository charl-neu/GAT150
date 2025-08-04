#pragma once
#include "../Core/StringHelperr.h"
#include <fmod.hpp>
#include <string>
#include <map>

namespace viper {
	class AudioSystem {
	public:
		bool Initialize();
		void Shutdown();

		void Update();

		bool AddSound(const std::string& filename, const std::string& name = "filename");
		bool PlaySound(const std::string& name);
	private:
		bool checkFMODResult(FMOD_RESULT result);

		FMOD::System* m_system = nullptr;
		std::map<std::string, FMOD::Sound*> m_sounds;
	};
}