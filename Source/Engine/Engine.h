#pragma once
#include "Core/Time.h"
#include "Core/Singleton.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Renderer.h"
#include "Audio/Audio System.h"
#include "Input/Input System.h"
#include "Renderer/Particle System.h"

#include <memory>

namespace viper
{
	class Engine : public Singleton<Engine>{
	public:

		static Engine& Instance() {
			static Engine instance;
			return instance;
		}

		bool Initialize();
		void Shutdown();

		void Update();
		void Draw();

		Renderer& GetRenderer() { return *m_renderer; }
		AudioSystem& GetAudioSystem() { return *m_audio; }
		InputSystem& GetInputSystem() { return *m_input; }
		ParticleSystem& GetParticleSystem() { return *m_particleSystem; }

		Time& GetTime() { return m_time; }

	private:
		friend class Singleton;
		Engine() = default;

	private:
		
		Time m_time;

		std::unique_ptr<Renderer> m_renderer;
		std::unique_ptr<AudioSystem> m_audio;
		std::unique_ptr<InputSystem> m_input;
		std::unique_ptr<ParticleSystem> m_particleSystem;
	};

	inline Engine& GetEngine() { return Engine::Instance(); }
}