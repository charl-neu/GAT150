#pragma once
#include "../../Engine/Game/Component.h"


class Rocket : public nebula::Component, public nebula::ICollidable
{
public:
	float accel = 200;
public:
	Rocket() = default;

	CLASS_PROTOTYPE(Rocket)
	
public:
	void onCollision(nebula::Actor* other);
	void Update(float deltaTime) override;
};