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

	// Inherited via Component
	void update(float deltaTime) override;

	void Read(const viper::json::value_t& value) override {
		Object::Read(value);

		JSON_READ(value, accel);
		JSON_READ(value, angularVel);
		JSON_READ(value, health);
		JSON_READ(value, firetimer);
		JSON_READ(value, invincibilityTimer);
	}
};