
#include "CircleCollider2d.h"

void viper::CircleCollider2d::update(float deltaTime)
{
    //
}

bool viper::CircleCollider2d::CheckCollision(const ColliderComponent& other) const
{

	float distance = (owner->transform.position - other.owner->transform.position).Length();
	auto circle_collider = dynamic_cast<const CircleCollider2d*>(&other);
	if (circle_collider) {
		float radii = radius + circle_collider->radius;
		if (distance <= radii) {
			return true; 
		}
	}
    return false;
}

void viper::CircleCollider2d::Read(const rapidjson::Value& value)
{
	Object::Read(value);
	JSON_READ(value, radius);
}
