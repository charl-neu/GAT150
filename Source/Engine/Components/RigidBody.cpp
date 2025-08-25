#include "RigidBody.h"

namespace viper {
	FACTORY_REGISTER(RigidBody)

	void RigidBody::Update(float deltaTime)
	{

		owner->transform.position += velocity * deltaTime;
		velocity *= (1.0f / (1.0f + damping * deltaTime));
	}

	void RigidBody::Read(const viper::json::value_t& value)
	{
		Object::Read(value);
		JSON_READ(value, damping);
		JSON_READ(value, velocity);
	}
}