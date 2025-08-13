#include "Actor.h"
#include "../Renderer/Model.h"
#include "../Renderer/Renderer.h"
#include "../Components/RendererComponent.h"

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
				return; 
			}
		}

		for (auto& component : m_components) {
			if (component) {
				component->update(deltaTime);
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

		for (auto& component : m_components) {
			if (component) {
				auto rendcomp = dynamic_cast<RendererComponent*>(component.get());
				if (rendcomp) {
					rendcomp->Draw(renderer);
				}
			}
		}

		if (m_texture) {
			renderer.DrawTextureRotated(m_texture.get(), transform.position.x, transform.position.y, transform.scale, transform.rotation);
		}
	}

	float Actor::GetRadius() {
		//if (m_texture) {
			return 50; // (m_texture->GetSize().Length() * 0.5f)* transform.scale * 0.5f;
		//}
		return 0;//
	}

	void Actor::AddComponent(std::unique_ptr<class Component> component)
	{
		component->owner = this; 
		m_components.push_back(std::move(component));
		
		
	}
} 