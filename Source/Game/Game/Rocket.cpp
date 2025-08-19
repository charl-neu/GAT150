#include "Rocket.h"
#include "Engine.h"
#include "GamePlayer.h"

FACTORY_REGISTER(Rocket)

void Rocket::Update(float deltaTime)
{
	/*
	viper::vec2 force = viper::vec2{ 1,0 }.Rotate(viper::DegToRad(transform.rotation)) * accel;
	auto rigidBody = GetComponent<viper::RigidBody>();
	if (rigidBody) {
		rigidBody->velocity = force;
	}

	transform.position.x = viper::Wrap(transform.position.x, 0.0f, (float) viper::GetEngine().GetRenderer().GetWidth());
	transform.position.y = viper::Wrap(transform.position.y, 0.0f, (float) viper::GetEngine().GetRenderer().GetHeight());

	viper::Particle particle;
	particle.position = transform.position;
	particle.velocity = viper::vec2{ -(rigidBody->velocity.x) + viper::random::getReal() * 50 - 25, -(rigidBody->velocity.y) + viper::random::getReal() * 50 - 25 };
	particle.color = viper::vec3{ 1.0f, 1.0f, 1.0f };
	particle.lifetime = .1f * viper::random::getReal();
	viper::GetEngine().GetParticleSystem().AddParticle(particle);



	Actor::Update(deltaTime);

	if (lifespan < 0.0f && tag == "rocket") {
		scene->GetGame()->resetMultiplier();
	}
	*/
}

void Rocket::onCollision(viper::Actor* other)
{
	if ((other->tag == "enemy" && owner->tag == "rocket") || (other->tag == "player" && owner->tag == "rockete")) {
		owner->destroyed = true;
		if (owner->tag == "rocket") {
			owner->scene->GetGame()->increaseMultiplier(0.10f);
		}
	}
}
