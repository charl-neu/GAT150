#pragma once
#include "Components/ColliderComponent.h"
namespace viper
{
	class CircleCollider2d : public ColliderComponent
	{
	public:
		float radius{ 50.0f }; 

		// Inherited via ColliderComponent
		void update(float deltaTime) override;
		bool CheckCollision(const ColliderComponent& other) const override;
	};
}