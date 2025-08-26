#pragma once
#include "../../Engine/Game/Component.h"
#include "../../Engine/Components/RigidBody.h"
#include "../../Engine/Physics/Collidable.h"

class Enemy : public viper::Component, public viper::ICollidable
{
public:
	float accel = 200;
	float angularVel = 90.0f;
	float firetimer = 3.0f;
	float maxfire = 5.0f;
	int m_points = 100;

	viper::RigidBody* m_rigidBody;
public:
	Enemy() = default;
	CLASS_PROTOTYPE(Enemy)

	void Start() override;
	void Update(float deltaTime) override;
	void onCollision(viper::Actor* other) override;

private:
	void Read(const viper::json::value_t& value) override {
		Object::Read(value);

		JSON_READ(value, accel);
		JSON_READ(value, angularVel);
		JSON_READ(value, firetimer);
		JSON_READ(value, maxfire);
		JSON_READ(value, m_points);
	}
};