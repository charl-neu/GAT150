#include "Enemy.h"
#include "GamePlayer.h"
#include "GameData.h"
#include "Rocket.h"

FACTORY_REGISTER(Enemy)


void Enemy::Update(float deltaTime)
{
	/*
	bool playerFound = false;

	Player* player = owner->scene->GetActorByName<Player>("Player");
	if (player) {
		viper::vec2 direction{ 0, 0 };
		direction = player->transform.position - owner->transform.position;

		viper::vec2 forward = { viper::vec2{1, 0}.Rotate(viper::DegToRad(owner->transform.rotation)) };
		direction = direction.Normalized();

		float angle = viper::vec2::SignedAngleBetween(forward, direction);
		angle = viper::sign(angle);
		owner->transform.rotation += viper::RadToDeg(angle * 2 * deltaTime);

		angle = viper::RadToDeg(viper::vec2::AngleBetween(forward, direction));
		playerFound = angle < 15.0f;
	}

	viper::vec2 force = viper::vec2{1,0}.Rotate(viper::DegToRad(owner->transform.rotation)) * accel;
	//velocity += force * deltaTime;
	auto rigidBody = owner->GetComponent<viper::RigidBody>();
	if (rigidBody) {
		rigidBody->velocity += force * deltaTime;
	}

	owner->transform.position.x = viper::Wrap(owner->transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
	owner->transform.position.y = viper::Wrap(owner->transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

	firetimer -= deltaTime;
	if (firetimer <= 0.0f && playerFound) {
		viper::Transform transform;
		transform.position = owner->transform.position;
		transform.rotation = owner->transform.rotation;
		transform.scale = 0.3f;
		auto rocket = std::make_unique<Actor>(transform);// , viper::Resources().Get<viper::Texture>("missile-1.png", viper::GetEngine().GetRenderer()));
		rocket->accel = 600.0f;
		rocket->name = "rockete";
		rocket->tag = "rockete";
		rocket->lifespan = 0.5f;

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
		firetimer = maxfire;
	}


	Actor::Update(deltaTime);
	*/
}

void Enemy::onCollision(viper::Actor* other)
{
	if (other->tag != owner->tag && other->tag != "rockete" && name != "immortal snail")
	{
		owner->destroyed = true;
		owner->scene->GetGame()->AddPoints(m_points);
		for (int i = 0; i < 100; i++)
		{
			viper::Particle particle;
			particle.position = owner->transform.position;
			particle.velocity = viper::vec2{ viper::random::getReal() * 2 - 1, viper::random::getReal() * 2 - 1 }.Normalized() * viper::random::getReal() * 100.0f;
			particle.color = viper::vec3{ 1.0f, 1.0f, 1.0f };
			particle.lifetime = .5f * (viper::random::getReal() * 2);
			viper::GetEngine().GetParticleSystem().AddParticle(particle);
		}
	}
}
