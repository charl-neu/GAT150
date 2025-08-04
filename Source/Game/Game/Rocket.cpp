#include "Rocket.h"
#include "Engine.h"
#include "Game/scene.h"
#include "Renderer/Renderer.h"
#include "GamePlayer.h"
#include "Core/Random.h"
#include "Renderer/Particle System.h"
#include "Game/Game.h"

void Rocket::Update(float deltaTime)
{
	viper::vec2 force = viper::vec2{ 1,0 }.Rotate(viper::DegToRad(transform.rotation)) * accel;
	velocity = force;

	transform.position.x = viper::Wrap(transform.position.x, 0.0f, (float) viper::GetEngine().GetRenderer().GetWidth());
	transform.position.y = viper::Wrap(transform.position.y, 0.0f, (float) viper::GetEngine().GetRenderer().GetHeight());

	viper::Particle particle;
	particle.position = transform.position;
	particle.velocity = viper::vec2{ -velocity.x + viper::random::getReal() * 50 - 25, -velocity.y + viper::random::getReal() * 50 - 25 };
	particle.color = viper::vec3{ 1.0f, 1.0f, 1.0f };
	particle.lifetime = .1f * viper::random::getReal();
	viper::GetEngine().GetParticleSystem().AddParticle(particle);



	Actor::Update(deltaTime);

	if (lifespan < 0.0f && tag == "rocket") {
		scene->GetGame()->resetMultiplier();
	}
}

void Rocket::onCollision(Actor* other)
{
	if ((other->tag == "enemy" && tag == "rocket") || (other->tag == "player" && tag == "rockete")) {
		destroyed = true;
		if (tag == "rocket") {
			scene->GetGame()->increaseMultiplier(0.10f);
		}
	}
}
