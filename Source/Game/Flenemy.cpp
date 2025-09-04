#include "Flenemy.h"

FACTORY_REGISTER(FlEnemyController)

void FlEnemyController::onCollision(viper::Actor* other)
{
}

void FlEnemyController::Start()
{
	m_rigidBody = owner->GetComponent<viper::RigidBody>();
}

void FlEnemyController::Update(float deltaTime)
{
	auto player = owner->scene->GetActorByName("pPlayer");
	if (player) {
		viper::vec2 toPlayer = player->transform.position - owner->transform.position;
		m_rigidBody->applyForce(toPlayer.Normalized() * accel);
	}

}
