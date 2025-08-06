#pragma once
#include "../Engine/Game/Actor.h"

class Rocket : public viper::Actor
{
public:
	float accel = 200;
	float angularVel = 120.0f;
public:
	Rocket() = default;
	Rocket(const viper::Transform& transform, viper::res_t<viper::Texture> texture) :
		Actor{ transform, texture }
	{ }
	

	void Update(float deltaTime) override;
private:

	// Inherited via Actor
	void onCollision(Actor* other) override;
};