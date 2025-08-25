#pragma once
#include "../../Engine/Game/Component.h"


class Rocket : public viper::Component, public viper::ICollidable
{
public:
	float accel = 200;
	float angularVel = 120.0f;
public:
	Rocket() = default;

	CLASS_PROTOTYPE(Rocket)
	
public:

	void onCollision(viper::Actor* other);

	// Inherited via Component
	void Update(float deltaTime) override;
};