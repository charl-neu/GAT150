#pragma once
#include "../../Engine/Game/Component.h"


class Player : public viper::Component
{
public:
	float accel = 200;
	float angularVel = 90.0f;
	int health = 3;
public:
	Player() = default;

	void Update(float deltaTime);
	
public:
	float firetimer = 0.0f;
	float invincibilityTimer = 0.0f;

	// Inherited via Actor
	void onCollision(viper::Actor* other);
};