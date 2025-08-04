#pragma once
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include <vector>

namespace viper {
	struct Particle
	{
		bool active{ false };
		float lifetime{ 1 };
		
		vec2 position;
		vec2 velocity;
		vec3 color;

	};

	class ParticleSystem
	{
	public:
		ParticleSystem() = default;

		bool Initialize(int poolsize = 10000);
		void Shutdown();

		void Update(float deltaTime);
		void Draw(class Renderer& renderer);

		void AddParticle(const Particle& particle);

	private:
		Particle* GetFreeParticle();
	private:
		std::vector<Particle> m_particles;

	};
}