#include "Rocket.h"
#include "Engine.h"
#include "GamePlayer.h"

FACTORY_REGISTER(Rocket)

void Rocket::Update(float deltaTime)
{
	
	nebula::vec2 force = nebula::vec2{ 1,0 }.Rotate(nebula::DegToRad(owner->transform.rotation)) * accel;
	auto rigidBody = owner->GetComponent<nebula::RigidBody>();

	if (rigidBody) {
		rigidBody->setVelocity(force);
	}

	owner->transform.position.x = nebula::Wrap(owner->transform.position.x, 0.0f, (float) nebula::GetEngine().GetRenderer().GetWidth());
	owner->transform.position.y = nebula::Wrap(owner->transform.position.y, 0.0f, (float) nebula::GetEngine().GetRenderer().GetHeight());

	nebula::Particle particle;
	particle.position = owner->transform.position;
	// Thrust particle effect the opposite direction of the rocket's movement
	particle.velocity = nebula::vec2{ -(force.x) + nebula::random::getReal() * 50 - 25, -(force.y) + nebula::random::getReal() * 50 - 25 };
	
	particle.color = nebula::vec3{ 1.0f, 1.0f, 1.0f };
	particle.lifetime = .1f * nebula::random::getReal();
	nebula::GetEngine().GetParticleSystem().AddParticle(particle);

	




	if ((owner->lifespan < 0.1f) && (owner->tag == "rocketp")) {
		owner->scene->GetGame()->resetMultiplier();
	}
	
}

void Rocket::onCollision(nebula::Actor* other)
{
	if ((other->tag == "enemy" && owner->name == "Rocketp") || (other->tag == "player" && owner->name == "Rockete")) {
		owner->destroyed = true;
		if (owner->tag == "rocketp") {
			owner->scene->GetGame()->increaseMultiplier(0.10f);
		}
	}
}
