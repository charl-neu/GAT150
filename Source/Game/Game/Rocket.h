#pragma once
#include "../../Engine/Game/Component.h"


class Rocket : public viper::Component
{
public:
	float accel = 200;
	float angularVel = 120.0f;
public:
	Rocket() = default;

	

	void Update(float deltaTime);
public:

	void onCollision(viper::Actor* other);

	// Inherited via Component
	void update(float deltaTime) override;
};