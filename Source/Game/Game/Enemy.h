#pragma once
#include "../Engine/Game/Actor.h"

class Enemy: public viper::Actor
{
public:
	float accel = 200;
	float angularVel = 90.0f;
	float firetimer = 3.0f;
	float maxfire = 5.0f;
	int m_points = 100;
public:
	Enemy() = default;
	Enemy(const viper::Transform& transform, std::shared_ptr<viper::Model> model) :
		Actor{ transform, model }
	{
	}

	void Update(float deltaTime) override;
private:

	// Inherited via Actor
	void onCollision(Actor* other) override;

};