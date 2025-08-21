#pragma once
#include "../../Engine/Game/Component.h"



class Enemy: public viper::Component
{
public:
	float accel = 200;
	float angularVel = 90.0f;
	float firetimer = 3.0f;
	float maxfire = 5.0f;
	int m_points = 100;
public:
	Enemy() = default;
	CLASS_PROTOTYPE(Enemy)

	void Update(float deltaTime);
	void onCollision(viper::Actor* other);
private:


	// Inherited via Component
	void update(float deltaTime) override;

};