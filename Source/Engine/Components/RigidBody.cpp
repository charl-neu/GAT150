#include "RigidBody.h"

void viper::RigidBody::update(float deltaTime)
{

	owner->transform.position += velocity * deltaTime;
	velocity *= (1.0f / (1.0f + damping * deltaTime));
}

void viper::RigidBody::Read(const viper::json::value_t& value)
{
	Object::Read(value);
	JSON_READ(value, damping);
	JSON_READ(value, velocity);
}