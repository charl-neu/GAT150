#include "CircleCollider2d.h"

namespace nebula {
	FACTORY_REGISTER(CircleCollider2d)

	void CircleCollider2d::Update(float deltaTime)
	{
		//
	}

	bool CircleCollider2d::CheckCollision(const ColliderComponent& other) const
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

	void CircleCollider2d::Read(const rapidjson::Value& value)
	{
		Object::Read(value);
		JSON_READ(value, radius);
	}

}
