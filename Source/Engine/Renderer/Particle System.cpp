#include "Particle System.h"
#include "Renderer.h"

namespace viper {
	bool ParticleSystem::Initialize(int poolsize) {
		m_particles.resize(poolsize); 
		return true;
	}

	void ParticleSystem::Shutdown() {
		m_particles.clear(); 

	}

	void ParticleSystem::Update(float deltaTime) {
		for(auto& particle : m_particles) {
			if (particle.active) {
				particle.lifetime -= deltaTime;
				if (particle.lifetime <= 0.0f) {
					particle.active = false; 
				} else {
					particle.position += particle.velocity * deltaTime; 
				}
			}
		}
	}

	void ParticleSystem::Draw(Renderer& renderer) {
		for (const auto& particle : m_particles) {
			if (particle.active) {
				renderer.SetColor(particle.color.x, particle.color.y, particle.color.z);
				renderer.DrawPoint(particle.position.x, particle.position.y);
			}
		}

	}

	void ParticleSystem::AddParticle(const Particle& particle) {
		Particle* freeParticle = GetFreeParticle();
		if (freeParticle) {
			*freeParticle = particle; 
			freeParticle->active = true; 
		}
		else {
		}
	}

	Particle* ParticleSystem::GetFreeParticle() {
		for (auto& particle : m_particles) {
			if (!particle.active) {
				return &particle;
			}
		}
		return nullptr; 
	}


}