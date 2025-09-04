#include "Physics.h"
#include "Game/Actor.h"

namespace nebula {
	bool Physics::Initialize() {
		b2WorldDef worldDef = b2DefaultWorldDef();
		worldDef.gravity = b2Vec2{ 0.0f, 10.0f };
		m_worldId = b2CreateWorld(&worldDef);

		return true;
	}

	void Physics::Shutdown() {
		b2DestroyWorld(m_worldId);
	}

	void Physics::Update(float dt) {
		b2World_Step(m_worldId, 1.0f / 60.0f, 4);
		ProcessCollisionEvents();
	}
	void Physics::ProcessCollisionEvents()
	{
		b2ContactEvents contactEvents = b2World_GetContactEvents(m_worldId);

		//std::cout << "Begin Contacts: " << contactEvents.beginCount << " End Contacts: " << contactEvents.endCount << std::endl;
		//begin contact
		for (int i = 0; i < contactEvents.beginCount; i++) {
			b2ContactBeginTouchEvent* contactEvent = contactEvents.beginEvents + i;

			if (!b2Shape_IsValid(contactEvent->shapeIdA) || !b2Shape_IsValid(contactEvent->shapeIdB)) continue;

			b2BodyId bodyA = b2Shape_GetBody(contactEvent->shapeIdA);
			b2BodyId bodyB = b2Shape_GetBody(contactEvent->shapeIdB);

			Actor* actorA = (Actor*)b2Body_GetUserData(bodyA);
			if (!actorA || actorA->destroyed || !actorA->active) continue;

			Actor* actorB = (Actor*)b2Body_GetUserData(bodyB);
			if (!actorA || actorA->destroyed || !actorA->active) continue;

			actorA->onCollision(actorB);
			actorB->onCollision(actorA);
		}

		//end contact
		for (int i = 0; i < contactEvents.endCount; i++) {
			b2ContactEndTouchEvent* contactEvent = contactEvents.endEvents + i;

			if (!b2Shape_IsValid(contactEvent->shapeIdA) || !b2Shape_IsValid(contactEvent->shapeIdB)) continue;

			b2BodyId bodyA = b2Shape_GetBody(contactEvent->shapeIdA);
			b2BodyId bodyB = b2Shape_GetBody(contactEvent->shapeIdB);

			Actor* actorA = (Actor*)b2Body_GetUserData(bodyA);
			if (!actorA || actorA->destroyed || !actorA->active) continue;

			Actor* actorB = (Actor*)b2Body_GetUserData(bodyB);
			if (!actorA || actorA->destroyed || !actorA->active) continue;

			actorA->onCollision(actorB);
			actorB->onCollision(actorA);
		}

		//sensor contact
		b2SensorEvents sensorEvents = b2World_GetSensorEvents(m_worldId);
		for (int i = 0; i < sensorEvents.beginCount; i++) {
			b2SensorBeginTouchEvent* contactEvent = sensorEvents.beginEvents + i;

			if (!b2Shape_IsValid(contactEvent->sensorShapeId) || !b2Shape_IsValid(contactEvent->visitorShapeId)) continue;

			b2BodyId bodyA = b2Shape_GetBody(contactEvent->sensorShapeId);
			b2BodyId bodyB = b2Shape_GetBody(contactEvent->visitorShapeId);

			Actor* actorA = (Actor*)b2Body_GetUserData(bodyA);
			if (!actorA || actorA->destroyed || !actorA->active) continue;

			Actor* actorB = (Actor*)b2Body_GetUserData(bodyB);
			if (!actorA || actorA->destroyed || !actorA->active) continue;

			actorA->onCollision(actorB);
			actorB->onCollision(actorA);
		}
	}
}
