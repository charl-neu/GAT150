#include "Actor.h"
#include "../Renderer/Renderer.h"
#include "../Components/RendererComponent.h"

namespace viper {
	FACTORY_REGISTER(Actor)

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

		//update all components
		for (auto& component : m_components) {
			if (component->active) {
				component->update(deltaTime);
			}
		}

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

		
	}



	void Actor::AddComponent(std::unique_ptr<class Component> component)
	{
		component->owner = this; 
		m_components.push_back(std::move(component));
		
		
	}

	void Actor::Read(const json::value_t& value)
	{
		Object::Read(value);

		JSON_READ(value, tag);
		JSON_READ(value, lifespan);

		if (JSON_HAS(value, transform)) transform.Read(JSON_GET(value, transform));

		//read components
		if (JSON_HAS(value, components)) {
			for (auto& componentValue : JSON_GET(value, components).GetArray()) {
				std::string type;
				JSON_READ(componentValue, type);

				auto component = Factory::Instance().Create<Component>(type);
				component->Read(componentValue);

				AddComponent(std::move(component));
			}
		}
	}
} 