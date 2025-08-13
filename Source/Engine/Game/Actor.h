#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Math/Vector2.h"
#include "Renderer/Texture.h"
#include "Component.h"
#include <string>
#include <memory>

namespace viper {
	class Actor : public Object{
	public:
		std::string tag;

		vec2 velocity{ 0 , 0 };
		float damping{ .2f };

		bool destroyed{ false }; 
		float lifespan{ -1.0f }; 

		Transform transform{ {0, 0}, 0, 1 };
		class Scene* scene{ nullptr };

	public:
		Actor() = default;
		Actor(const Transform& transform) :
			transform{ transform }
		{
		}
	


		virtual void Update(float deltaTime);
		virtual void Draw(class Renderer& renderer);

		virtual void onCollision(Actor* other) = 0;

		float GetRadius();

		//components

		void AddComponent(std::unique_ptr<Component> component);

	protected:
		std::vector < std::unique_ptr <Component >> m_components;
		res_t<Texture> m_texture;
		//std::shared_ptr<Model> m_model;
	};
}