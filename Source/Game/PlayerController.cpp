#include "PlayerController.h"

FACTORY_REGISTER(PlayerController)

void PlayerController::onCollision(nebula::Actor* other)
{
	if (other->tag == "enemy" && invincibilityTimer < 0.0f) {
		health--;
		invincibilityTimer = 2.0f;
		if (health <= 0) {
			owner->destroyed = true; \
			nebula::EventManager::Instance().Notify(nebula::Event{ "Player_dead", true });
		}
	}
}

void PlayerController::Start()
{
	m_rigidBody = owner->GetComponent<nebula::RigidBody>();
}

void PlayerController::Update(float deltaTime)
{

	float dir = 0;
	if (nebula::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_A)) {
		dir = -1;
	}

	if (nebula::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_D)) {
		dir = 1;
	}

	if (dir != 0) {
		m_rigidBody->applyForce(nebula::vec2{ 1,0 } *dir * accel * 10);
	}

	if (fabs(m_rigidBody->velocity.x) > maxspeed) m_rigidBody->setVelocity({ maxspeed, m_rigidBody->velocity.y });

  	if (nebula::GetEngine().GetInputSystem().GetKeyPressed(SDL_SCANCODE_SPACE)) {
		m_rigidBody->setVelocity(nebula::vec2{ m_rigidBody->velocity.x, -1 * jump * 100 });
	}

	auto spriteRenderer = owner->GetComponent<nebula::SpriteRenderer>();
	if (spriteRenderer) {
		if (nebula::fabs(m_rigidBody->velocity.x) != 0) {
			spriteRenderer->fliph = (m_rigidBody->velocity.x < 0);
		}
	}
	invincibilityTimer -= deltaTime;
}
