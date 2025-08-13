#pragma once
#include "../Engine/Game/Actor.h"

class Player : public viper::Actor
{
public:
	float accel = 200;
	float angularVel = 90.0f;
	int health = 3;
public:
	Player() = default;
	Player(const viper::Transform& transform) :
		Actor{ transform} 
	{}

	void Update(float deltaTime) override;
	
private:
	float firetimer = 0.0f;
	float invincibilityTimer = 0.0f;

	// Inherited via Actor
	void onCollision(Actor* other) override;
};