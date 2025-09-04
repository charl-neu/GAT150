#include "PlayerController.h"

FACTORY_REGISTER(PlayerController)

void PlayerController::onCollision(viper::Actor* other)
{
	std::cout << "Collided with " << other->name << std::endl;
	if (other->tag == "enemy" && invincibilityTimer < 0.0f) {
		health--;
		invincibilityTimer = 2.0f;
		if (health <= 0) {
			owner->destroyed = true; \
			viper::EventManager::Instance().Notify(viper::Event{ "Player_dead", true });
		}
	}
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
		m_rigidBody->applyForce(viper::vec2{ 1,0 } *dir * accel * 10);
	}

	if (fabs(m_rigidBody->velocity.x) > maxspeed) m_rigidBody->setVelocity({ maxspeed, m_rigidBody->velocity.y });

  	if (viper::GetEngine().GetInputSystem().GetKeyPressed(SDL_SCANCODE_SPACE)) {
		m_rigidBody->setVelocity(viper::vec2{ m_rigidBody->velocity.x, -1 * jump * 100 });
	}

	auto spriteRenderer = owner->GetComponent<viper::SpriteRenderer>();
	if (spriteRenderer) {
		if (viper::fabs(m_rigidBody->velocity.x) != 0) {
			spriteRenderer->fliph = (m_rigidBody->velocity.x < 0);
		}
	}
	invincibilityTimer -= deltaTime;
}
