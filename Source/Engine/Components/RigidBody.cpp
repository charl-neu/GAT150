#include "RigidBody.h"

void viper::RigidBody::update(float deltaTime)
{

	owner->transform.position += velocity * deltaTime;
	velocity *= (1.0f / (1.0f + damping * deltaTime));
}
