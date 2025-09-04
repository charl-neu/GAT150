#include "EnemyController.h"

FACTORY_REGISTER(EnemyController)

void EnemyController::onCollision(viper::Actor* other)
{
	if (other->tag == "player") {
		owner->destroyed = true;
	}
}

void EnemyController::Start()
{
	m_rigidBody = owner->GetComponent<viper::RigidBody>();
}

void EnemyController::Update(float deltaTime)
{
	float dir = 0;
	
	auto actor = owner->scene->GetActorByName<viper::Actor>("pPlayer");
	if (actor) {
		if (actor->transform.position.x < owner->transform.position.x) dir = -1;
		else dir = 1;
	}

	if (dir != 0) {
		m_rigidBody->applyForce(viper::vec2{ 1,0 } * dir * accel * 10);
	}

}
