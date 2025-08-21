#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Math/Vector2.h"
#include "Renderer/Texture.h"
#include "Component.h"
#include <string>
#include <memory>

namespace viper {
	class Actor : public Object {
	public:
		std::string tag;
		float lifespan{ -1.0f }; 
		bool persistent{ false }; // if true, actor will not be destroyed when the scene is cleared

		Transform transform{ {0, 0}, 0, 1 };

		bool destroyed{ false }; 
		class Scene* scene{ nullptr };

	public:
		Actor() = default;
		Actor(const Transform& transform) :
			transform{ transform }
		{
		}
		Actor(const Actor& other);

		CLASS_PROTOTYPE(Actor)

		virtual void Update(float deltaTime);
		virtual void Draw(class Renderer& renderer);

		virtual void onCollision(Actor* other) {}

		//components

		void AddComponent(std::unique_ptr<Component> component);

		template<typename T>
		T* GetComponent();

		template<typename T>
		std::vector<T*> GetComponents();

		void Read(const json::value_t& value) override;

	protected:
		std::vector < std::unique_ptr <Component >> m_components;
	};

	template <typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : m_components) {
			auto result = dynamic_cast<T*>(component.get());
			if (result) {
				return result;
			}
		}
		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Actor::GetComponents()
	{
		std::vector<T*> results;
		for (auto& component : m_components) {
			auto result = dynamic_cast<T*>(component.get());
			if (result) {
				results.push_back(result);
			}
		}
		return results;
	}
}