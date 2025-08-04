#include "Actor.h"
#include "../Renderer/Model.h"
#include "../Renderer/Renderer.h"

namespace viper {
	/// <summary>
	/// Updates the actor's state based on the elapsed time.
	/// </summary>
	/// <param name="deltaTime">The time elapsed since the last update.</param>
	void Actor::Update(float deltaTime) {
		if (destroyed) {
			return; 
		}

		if (lifespan > 0.0f) {
			lifespan -= deltaTime;
			if (lifespan <= 0.0f) {
				destroyed = true; 
			}
		}

		transform.position += velocity * deltaTime;
		velocity *= (1.0f / (1.0f + damping * deltaTime)); 
	}

	/// <summary>
	/// Draws the actor using the specified renderer.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the actor.</param>
	void Actor::Draw(Renderer& renderer) {

		if (destroyed) {
			return; 
		}

		if (m_model) {
			m_model->Draw(renderer, transform);
		}
	}

	float Actor::GetRadius() {
		if (m_model) {
			return m_model->GetRadius() * transform.scale; 
		}
		return 0.0f; 
	}
} 