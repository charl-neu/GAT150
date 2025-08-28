#include "Rocket.h"
#include "Engine.h"
#include "GamePlayer.h"

FACTORY_REGISTER(Rocket)

void Rocket::Update(float deltaTime)
{
	
	viper::vec2 force = viper::vec2{ 1,0 }.Rotate(viper::DegToRad(owner->transform.rotation)) * accel;
	auto rigidBody = owner->GetComponent<viper::RigidBody>();

	if (rigidBody) {
		rigidBody->setVelocity(force);
	}

	owner->transform.position.x = viper::Wrap(owner->transform.position.x, 0.0f, (float) viper::GetEngine().GetRenderer().GetWidth());
	owner->transform.position.y = viper::Wrap(owner->transform.position.y, 0.0f, (float) viper::GetEngine().GetRenderer().GetHeight());

	viper::Particle particle;
	particle.position = owner->transform.position;
	// Thrust particle effect the opposite direction of the rocket's movement
	particle.velocity = viper::vec2{ -(force.x) + viper::random::getReal() * 50 - 25, -(force.y) + viper::random::getReal() * 50 - 25 };
	
	particle.color = viper::vec3{ 1.0f, 1.0f, 1.0f };
	particle.lifetime = .1f * viper::random::getReal();
	viper::GetEngine().GetParticleSystem().AddParticle(particle);

	




	if ((owner->lifespan < 0.1f) && (owner->tag == "rocketp")) {
		owner->scene->GetGame()->resetMultiplier();
	}
	
}

void Rocket::onCollision(viper::Actor* other)
{
	if ((other->tag == "enemy" && owner->name == "Rocketp") || (other->tag == "player" && owner->name == "Rockete")) {
		owner->destroyed = true;
		if (owner->tag == "rocketp") {
			owner->scene->GetGame()->increaseMultiplier(0.10f);
		}
	}
}
