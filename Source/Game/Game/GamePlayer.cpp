#include "../GamePCH.h"
#include "GamePlayer.h"
#include "Rocket.h"
#include "Engine.h"
#include "GameData.h"
#include "GameGame.h"

FACTORY_REGISTER(Player)

void Player::Start() {
	m_rigidBody = owner->GetComponent<nebula::RigidBody>();
}

void Player::Update(float deltaTime)
{
	if (m_rigidBody->velocity.Length()) {
		nebula::Particle particle;
		particle.position = owner->transform.position;
		particle.velocity = nebula::vec2{ -(m_rigidBody->velocity.x) + nebula::random::getReal() * 100 - 50, -(m_rigidBody->velocity.y) + nebula::random::getReal() * 100 - 50 };
		particle.color = nebula::vec3{ 1.0f, 1.0f, 1.0f };
		particle.lifetime = .25f * (nebula::random::getReal() * 2);
		nebula::GetEngine().GetParticleSystem().AddParticle(particle);
	}


	float rotate = 0;
	

	if (nebula::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_A)) {
		rotate = -1;
	}

	if (nebula::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_D)) {
		rotate = 1;
	}

	owner->transform.rotation += rotate * deltaTime * angularVel;

	m_rigidBody->applyTorque(rotate);

	float thrust = 0;
	if (nebula::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_W)) {
		thrust = 1;
	}
	if (nebula::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_S)) {
		thrust = -.5;
	}


	nebula::vec2 direction{ 1, 0 };
	nebula::vec2 force = direction.Rotate(nebula::DegToRad(owner->transform.rotation)) * accel * thrust;
	if (m_rigidBody) {
		m_rigidBody->applyForce(force);
	}
	owner->transform.position.x = nebula::Wrap(owner->transform.position.x, 0.0f, 1280.0f);
	owner->transform.position.y = nebula::Wrap(owner->transform.position.y, 0.0f, 1024.0f);

	
	if (nebula::GetEngine().GetInputSystem().GetKeyPressed(SDL_SCANCODE_SPACE)) {
		if(firetimer <= 0.0f) {
			auto sound = nebula::Resources().Get<nebula::AudioClip>("bass.wav", nebula::GetEngine().GetAudioSystem());
			if (sound) {
				nebula::GetEngine().GetAudioSystem().PlaySound(*sound);
			}
			
			nebula::Transform transform{ owner->transform.position, owner->transform.rotation, 0.5f };
			auto rock = nebula::Instantiate("Rocketp", transform);
			owner->scene->AddActor(std::move(rock), true);

			firetimer = 0.25f;

			
		}
	}
	

	firetimer -= deltaTime;
	invincibilityTimer -= deltaTime;
	



}

void Player::onCollision(nebula::Actor* other)
{
	if ((other->tag == "enemy" || other->tag == "rockete") && invincibilityTimer < 0) {
		health--;
		if (health <= 0) {
			owner->destroyed = true;
			invincibilityTimer = 2.0f; // Start invincibility timer
			nebula::EventManager::Instance().Notify(nebula::Event{ "Player_dead", true });
			//dynamic_cast<SpaceGame*>(owner->scene->GetGame())->OnPlayerDeath();
		}
	}
}

