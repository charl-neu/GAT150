#pragma once
#include "../../Engine/Game/Component.h"


class Player : public nebula::Component, public nebula::ICollidable
{
public:
	float accel = 200;
	float angularVel = 90.0f;
	int health = 3;

	nebula::RigidBody* m_rigidBody;
public:
	Player() = default;
	CLASS_PROTOTYPE(Player)

	
public:
	float firetimer = 0.0f;
	float invincibilityTimer = 0.0f;

	

	// Inherited via Actor
	void onCollision(nebula::Actor* other) override;

	void Start() override;

	// Inherited via Component
	void Update(float deltaTime) override;

	void Read(const nebula::json::value_t& value) override {
		Object::Read(value);

		JSON_READ(value, accel);
		JSON_READ(value, angularVel);
		JSON_READ(value, health);
		JSON_READ(value, firetimer);
		JSON_READ(value, invincibilityTimer);
	}
};