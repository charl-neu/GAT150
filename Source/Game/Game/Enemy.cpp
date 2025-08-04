#include "Enemy.h"
#include "Engine.h"
#include "Game/scene.h"
#include "Renderer/Renderer.h"
#include "GamePlayer.h"
#include "Game/Game.h"
#include "Core/Random.h"
#include "Renderer/Particle System.h"
#include "GameData.h"
#include "Rocket.h"
#include "Math/Vector2.h"
#include "Renderer/Model.h"


void Enemy::Update(float deltaTime)
{
	bool playerFound = false;

	Player* player = scene->GetActorByName<Player>("Player");
	if (player) {
		viper::vec2 direction{ 0, 0 };
		direction = player->transform.position - transform.position;

		viper::vec2 forward = { viper::vec2{1, 0}.Rotate(viper::DegToRad(transform.rotation)) };
		direction = direction.Normalized();

		float angle = viper::vec2::SignedAngleBetween(forward, direction);
		angle = viper::sign(angle);
		transform.rotation += viper::RadToDeg(angle * 2 * deltaTime);

		angle = viper::RadToDeg(viper::vec2::AngleBetween(forward, direction));
		playerFound = angle < 15.0f;
	}

	viper::vec2 force = viper::vec2{1,0}.Rotate(viper::DegToRad(transform.rotation)) * accel;
	velocity += force * deltaTime;

	transform.position.x = viper::Wrap(transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
	transform.position.y = viper::Wrap(transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

	firetimer -= deltaTime;
	if (firetimer <= 0.0f && playerFound) {
		std::shared_ptr<viper::Model> ro_model = std::make_shared<viper::Model>(GameData::ro_points, viper::vec3{ 1.0f, 0, 0 });
		viper::Transform shape{ viper::vec2{transform.position.x, transform.position.y}, transform.rotation, 1.0f };
		auto rocket = std::make_unique<Rocket>(shape, ro_model);
		rocket->accel = 600.0f;
		rocket->damping = 0.0f;
		rocket->name = "rockete";
		rocket->tag = "rockete";
		rocket->lifespan = 0.5f;
		scene->AddActor(std::move(rocket));
		firetimer = maxfire;
	}


	Actor::Update(deltaTime);
}

void Enemy::onCollision(Actor* other)
{
	if (other->tag != this->tag && other->tag != "rockete" && name != "immortal snail")
	{
		destroyed = true;
		scene->GetGame()->AddPoints(m_points);
		for (int i = 0; i < 100; i++)
		{
			viper::Particle particle;
			particle.position = transform.position;
			particle.velocity = viper::vec2{ viper::random::getReal() * 2 - 1, viper::random::getReal() * 2 - 1 }.Normalized() * viper::random::getReal() * 100.0f;
			particle.color = viper::vec3{ 1.0f, 1.0f, 1.0f };
			particle.lifetime = .5f * (viper::random::getReal() * 2);
			viper::GetEngine().GetParticleSystem().AddParticle(particle);
		}
	}
}
