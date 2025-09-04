#include "PlayerController.h"

FACTORY_REGISTER(PlayerController)

void PlayerController::onCollision(viper::Actor* other)
{
	std::cout << "Collided with " << other->name << std::endl;
}

void PlayerController::Start()
{
	m_rigidBody = owner->GetComponent<viper::RigidBody>();
}

void PlayerController::Update(float deltaTime)
{
	float dir = 0;
	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_A)) {
		dir = -1;
	}

	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_D)) {
		dir = 1;
	}

	if (dir != 0) {
		m_rigidBody->applyForce(viper::vec2{ 1,0 } * dir * accel * 10);
	}

	if (viper::GetEngine().GetInputSystem().GetKeyPressed(SDL_SCANCODE_SPACE)) {
		m_rigidBody->applyForce(viper::vec2{ 0,-1 } * jump * 10000);
	}

	auto spriteRenderer = owner->GetComponent<viper::SpriteRenderer>();
	if (spriteRenderer) {
		if (viper::fabs(m_rigidBody->velocity.x) != 0) {
			spriteRenderer->fliph = (m_rigidBody->velocity.x < 0);
		}
	}
}
