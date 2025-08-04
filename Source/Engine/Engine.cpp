#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Audio/Audio System.h"
#include "Input/Input System.h"
#include "Renderer/Particle System.h"

namespace viper
{

	Engine& GetEngine()
	{
		static Engine engine;
		return engine;
	}

	bool Engine::Initialize() 
	{
		m_renderer = std::make_unique<Renderer>();
		m_renderer->Initialize();
		m_renderer->CreateWindow("Viper Engine", 1280, 1024);

		m_input = std::make_unique<InputSystem>();
		m_input->Initialize();

		m_audio = std::make_unique<AudioSystem>();;
		m_audio->Initialize();

		m_particleSystem = std::make_unique<ParticleSystem>();
		m_particleSystem->Initialize();
		return true;
	}

	void Engine::Shutdown() 
	{
		if (m_particleSystem) {
			m_particleSystem->Shutdown();
		}
		if (m_audio) {
			m_audio->Shutdown();
		}

		if (m_input) {
			m_input->Shutdown();
		}

		if (m_renderer) {
			m_renderer->Shutdown();
		}

	}

	void Engine::Update() 
	{
		m_time.Tick();

		m_input->Update();
		m_audio->Update();	

	}

	void Engine::Draw()
	{

	}

}