#pragma once
#include "Game/Component.h"


class PlayerController : public viper::Component, public viper::ICollidable
{
public:
	float accel = 200;
	float maxspeed = 90.0f;
	float jump = 10.0f;
	int health = 3;

	viper::RigidBody* m_rigidBody;
public:
	PlayerController() = default;
	CLASS_PROTOTYPE(PlayerController)


public:
	float firetimer = 0.0f;
	float invincibilityTimer = 0.0f;



	void Start() override;

	void Update(float deltaTime) override;

	void onCollision(viper::Actor* other) override;

	void Read(const viper::json::value_t& value) override {
		Object::Read(value);

		JSON_READ(value, accel);
		JSON_READ(value, maxspeed);
		JSON_READ(value, health);
		JSON_READ(value, jump);
	}
};