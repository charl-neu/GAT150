#pragma once
#include "Components/ColliderComponent.h"
namespace nebula
{
	
	class CircleCollider2d : public ColliderComponent
	{
	public:
		float radius{ 50.0f }; 
		CLASS_PROTOTYPE(CircleCollider2d)

		// Inherited via ColliderComponent
		void Update(float deltaTime) override;
		bool CheckCollision(const ColliderComponent& other) const override;
		void Read(const rapidjson::Value& value);
	};
}