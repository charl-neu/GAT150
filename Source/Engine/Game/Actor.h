#pragma once
#include "../Math/Transform.h"
#include "../Math/Vector2.h"
#include <string>
#include <memory>

namespace viper {
	class Actor {
	public:
		std::string name;
		std::string tag;

		vec2 velocity{ 0 , 0 };
		float damping{ .2f };

		bool destroyed{ false }; 
		float lifespan{ -1.0f }; 

		Transform transform{ {0, 0}, 0, 1 };
		class Scene* scene{ nullptr };

	public:
		Actor() = default;
		Actor(const Transform& transform, std::shared_ptr<class Model> model) : transform(transform), m_model{ model } {}

		virtual void Update(float deltaTime);
		virtual void Draw(class Renderer& renderer);

		virtual void onCollision(Actor* other) = 0;

		float GetRadius();

	protected:
		std::shared_ptr<Model> m_model;
	};
}