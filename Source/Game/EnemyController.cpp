#include "EnemyController.h"

FACTORY_REGISTER(EnemyController)

void EnemyController::onCollision(nebula::Actor* other)
{
	if (other->tag == "player") {
		owner->destroyed = true;
	}
}

void EnemyController::Start()
{
	m_rigidBody = owner->GetComponent<nebula::RigidBody>();
}

void EnemyController::Update(float deltaTime)
{
	float dir = 0;
	
	auto actor = owner->scene->GetActorByName<nebula::Actor>("pPlayer");
	if (actor) {
		if (actor->transform.position.x < owner->transform.position.x) dir = -1;
		else dir = 1;
	}

	if (dir != 0) {
		m_rigidBody->applyForce(nebula::vec2{ 1,0 } * dir * accel * 10);
	}

}
