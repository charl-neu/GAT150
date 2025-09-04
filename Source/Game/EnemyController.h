#pragma once
#include "Game/Component.h"


class EnemyController : public nebula::Component, public nebula::ICollidable
{
public:
	float accel = 200;
	float maxspeed = 90.0f;
	float jump = 10.0f;
	int health = 3;

	nebula::RigidBody* m_rigidBody;
public:
	EnemyController() = default;
	CLASS_PROTOTYPE(EnemyController)


public:
	float firetimer = 0.0f;
	float invincibilityTimer = 0.0f;



	void Start() override;

	void Update(float deltaTime) override;

	void onCollision(nebula::Actor* other) override;

	void Read(const nebula::json::value_t& value) override {
		Object::Read(value);

		JSON_READ(value, accel);
		JSON_READ(value, maxspeed);
		JSON_READ(value, health);
		JSON_READ(value, jump);
	}
};