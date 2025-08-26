#include "Enemy.h"
#include "GamePlayer.h"
#include "GameData.h"
#include "Rocket.h"


FACTORY_REGISTER(Enemy) 


void Enemy::Start()
{
	m_rigidBody = owner->GetComponent<viper::RigidBody>();
}

void Enemy::Update(float deltaTime)
{
	
	bool playerFound = false;


	auto actor = owner->scene->GetActorByName<viper::Actor>("Player");
	Player* player = nullptr;
	if (actor) {
		player = actor->GetComponent<Player>();
	}

	if (player) {
		viper::vec2 direction{ 0, 0 };
		direction = player->owner->transform.position - owner->transform.position;

		viper::vec2 forward = { viper::vec2{1, 0}.Rotate(viper::DegToRad(owner->transform.rotation)) };
		direction = direction.Normalized();

		float angle = viper::vec2::SignedAngleBetween(forward, direction);
		angle = viper::sign(angle);
		owner->transform.rotation += viper::RadToDeg(angle * 2 * deltaTime);

		angle = viper::RadToDeg(viper::vec2::AngleBetween(forward, direction));
		playerFound = angle < 15.0f;
	}

	viper::vec2 force = viper::vec2{1,0}.Rotate(viper::DegToRad(owner->transform.rotation)) * accel;
	auto rigidBody = owner->GetComponent<viper::RigidBody>();
	if (rigidBody) {
		rigidBody->velocity += force * deltaTime;
	}

	owner->transform.position.x = viper::Wrap(owner->transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
	owner->transform.position.y = viper::Wrap(owner->transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

	firetimer -= deltaTime;
	if (firetimer <= 0.0f && playerFound && maxfire > 0) {
		viper::Transform transform{ owner->transform.position, owner->transform.rotation, 0.5f };
		auto rock = viper::Instantiate("Rockete", transform);
		owner->scene->AddActor(std::move(rock), true);
		firetimer = maxfire;

	}


	
}

void Enemy::onCollision(viper::Actor* other)
{
	if (other->tag != owner->tag && other->tag != "rockete" && owner->name != "IEnemy")
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

