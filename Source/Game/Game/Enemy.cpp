#include "Enemy.h"
#include "GamePlayer.h"
#include "GameData.h"
#include "Rocket.h"


FACTORY_REGISTER(Enemy) 


void Enemy::Start()
{
	nebula::EventManager::Instance().AddObserver("Player_dead", *this);

	m_rigidBody = owner->GetComponent<nebula::RigidBody>();
}

void Enemy::Update(float deltaTime)
{
	
	bool playerFound = false;


	auto actor = owner->scene->GetActorByName<nebula::Actor>("Player");
	Player* player = nullptr;
	if (actor) {
		player = actor->GetComponent<Player>();
	}

	if (player) {
		nebula::vec2 direction{ 0, 0 };
		direction = player->owner->transform.position - owner->transform.position;

		nebula::vec2 forward = { nebula::vec2{1, 0}.Rotate(nebula::DegToRad(owner->transform.rotation)) };
		direction = direction.Normalized();

		float angle = nebula::vec2::SignedAngleBetween(forward, direction);
		angle = nebula::sign(angle);
		m_rigidBody->applyTorque(angle*2);
		angle = nebula::RadToDeg(nebula::vec2::AngleBetween(forward, direction));
		playerFound = angle < 15.0f;
	}

	nebula::vec2 force = nebula::vec2{1,0}.Rotate(nebula::DegToRad(owner->transform.rotation)) * accel;
	
	m_rigidBody->applyForce(force);

	owner->transform.position.x = nebula::Wrap(owner->transform.position.x, 0.0f, (float)nebula::GetEngine().GetRenderer().GetWidth());
	owner->transform.position.y = nebula::Wrap(owner->transform.position.y, 0.0f, (float)nebula::GetEngine().GetRenderer().GetHeight());

	firetimer -= deltaTime;
	if (firetimer <= 0.0f && playerFound && maxfire > 0) {
		nebula::Transform transform{ owner->transform.position, owner->transform.rotation, 0.5f };
		auto rock = nebula::Instantiate("Rockete", transform);
		owner->scene->AddActor(std::move(rock), true);
		firetimer = maxfire;

	}


	
}

void Enemy::onCollision(nebula::Actor* other)
{
	if (other->tag != owner->tag && other->tag != "rockete" && owner->name != "IEnemy")
	{
		owner->destroyed = true;
		nebula::EventManager::Instance().Notify({ "add_pts", m_points });
		for (int i = 0; i < 100; i++)
		{
			nebula::Particle particle;
			particle.position = owner->transform.position;
			particle.velocity = nebula::vec2{ nebula::random::getReal() * 2 - 1, nebula::random::getReal() * 2 - 1 }.Normalized() * nebula::random::getReal() * 100.0f;
			particle.color = nebula::vec3{ 1.0f, 1.0f, 1.0f };
			particle.lifetime = .5f * (nebula::random::getReal() * 2);
			nebula::GetEngine().GetParticleSystem().AddParticle(particle);
		}
	}
}

void Enemy::OnNotify(const nebula::Event& event)
{
}

