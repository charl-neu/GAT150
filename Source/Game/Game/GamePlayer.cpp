#include "../GamePCH.h"
#include "GamePlayer.h"
#include "Rocket.h"
#include "Engine.h"
#include "GameData.h"
#include "GameGame.h"

FACTORY_REGISTER(Player)

void Player::Update(float deltaTime)
{
	
	auto rigidBody = owner->GetComponent<viper::RigidBody>();

	if (rigidBody->velocity.Length()) {
		viper::Particle particle;
		particle.position = owner->transform.position;
		particle.velocity = viper::vec2{ -(rigidBody->velocity.x) + viper::random::getReal() * 100 - 50, -(rigidBody->velocity.y) + viper::random::getReal() * 100 - 50 };
		particle.color = viper::vec3{ 1.0f, 1.0f, 1.0f };
		particle.lifetime = .25f * (viper::random::getReal() * 2);
		viper::GetEngine().GetParticleSystem().AddParticle(particle);
	}


	float rotate = 0;
	

	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_A)) {
		rotate = -1;
	}

	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_D)) {
		rotate = 1;
	}

	owner->transform.rotation += rotate * deltaTime * angularVel;



	float thrust = 0;
	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_W)) {
		thrust = 1;
	}
	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_S)) {
		thrust = -.5;
	}


	viper::vec2 direction{ 1, 0 };
	viper::vec2 force = direction.Rotate(viper::DegToRad(owner->transform.rotation)) * accel;
	if (rigidBody) {
		rigidBody->velocity += force * thrust * deltaTime;
	}
	owner->transform.position.x = viper::Wrap(owner->transform.position.x, 0.0f, 1280.0f);
	owner->transform.position.y = viper::Wrap(owner->transform.position.y, 0.0f, 1024.0f);

	/*
	if (viper::GetEngine().GetInputSystem().GetKeyPressed(SDL_SCANCODE_SPACE)) {
		if(firetimer <= 0.0f) {
			auto sound = viper::Resources().Get<viper::AudioClip>("bass.wav", viper::GetEngine().GetAudioSystem());
			if (sound) {
				viper::GetEngine().GetAudioSystem().PlaySound(*sound);
			}
			
			viper::Transform transform;
			transform.position = this->transform.position;
			transform.rotation = this->transform.rotation;
			transform.scale = 0.5f;
			auto rocket = std::make_unique<Rocket>(transform); // viper::Resources().Get<viper::Texture>("missile-1.png", viper::GetEngine().GetRenderer()));
			rocket->accel = 600.0f;
			rocket->name = "rocket";
			rocket->tag = "rocket";
			rocket->lifespan = 1.5f;

			auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
			spriteRenderer->textureName = "missile-1.png";
			rocket->AddComponent(std::move(spriteRenderer));


			auto rigidBody = std::make_unique<viper::RigidBody>();
			rigidBody->damping = 0.0f;
			rocket->AddComponent(std::move(rigidBody));

			auto collider = std::make_unique<viper::CircleCollider2d>();
			collider->radius = 10.0f;
			rocket->AddComponent(std::move(collider));

			scene->AddActor(std::move(rocket));
			firetimer = 0.2f;
			// TODO: Firing Sound viper::GetEngine().GetAudioSystem().PlaySound("fire");
		}
	}

	firetimer -= deltaTime;
	invincibilityTimer -= deltaTime;

	Actor::Update(deltaTime);
	*/

}

void Player::onCollision(viper::Actor* other)
{
	if ((other->tag == "enemy" || other->tag == "rockete") && invincibilityTimer < 0) {
		health--;
		if (health <= 0) {
			owner->destroyed = true;
			invincibilityTimer = 2.0f; // Start invincibility timer
			dynamic_cast<SpaceGame*>(owner->scene->GetGame())->OnPlayerDeath();
		}
	}
}

