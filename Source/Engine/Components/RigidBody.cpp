#include "RigidBody.h"
#include "SpriteRenderer.h"
#include "Engine.h"

namespace viper {
	FACTORY_REGISTER(RigidBody)

	RigidBody::RigidBody(const RigidBody& other)
	{
		bodyDef = other.bodyDef;
		size = other.size;

		if (other.m_physicsbody) {
			m_physicsbody = std::make_unique<PhysicsBody>(*other.m_physicsbody);
		}
	}

	void RigidBody::Start() {
		bodyDef.actor = owner;
		if (size.x == 0 && size.y == 0) {
			auto spriteRenderer = owner->GetComponent<SpriteRenderer>();
			if (spriteRenderer) {
				size = spriteRenderer->texture->GetSize();
			}
		}

		m_physicsbody = std::make_unique<PhysicsBody>(owner->transform, size, bodyDef, GetEngine().GetPhysics());
	}

	void RigidBody::applyForce(const vec2& force) {
		m_physicsbody->applyForce(force);
	}

	void RigidBody::applyTorque(float radians) {
		m_physicsbody->applyTorque(radians);
	}

	void RigidBody::setVelocity(const vec2& velocity) {
		m_physicsbody->setVelocity(velocity);
	}

	void RigidBody::Update(float deltaTime)
	{
		owner->transform.position = m_physicsbody->GetPosition();
		owner->transform.rotation = RadToDeg(m_physicsbody->GetAngle());
		velocity = m_physicsbody->Getvelocity();

	}

	void RigidBody::Read(const viper::json::value_t& value)
	{
		Object::Read(value);

		JSON_READ(value, size);

		JSON_READ(value, scale);

		JSON_READ_NAME(value, "gravityScale", bodyDef.gravityScale);

		JSON_READ_NAME(value, "linearDamping", bodyDef.linearDamping);

		JSON_READ_NAME(value, "angularDamping", bodyDef.angularDamping);

		JSON_READ_NAME(value, "constrainAngle", bodyDef.constrainAngle);

		JSON_READ_NAME(value, "isDynamic", bodyDef.isDynamic);

		JSON_READ_NAME(value, "friction", bodyDef.friction);

		JSON_READ_NAME(value, "restitution", bodyDef.restitution);

		JSON_READ_NAME(value, "density", bodyDef.density);

		JSON_READ_NAME(value, "isSensor", bodyDef.isSensor);

		std::string shapeName;

		JSON_READ_NAME(value, "shape", shapeName);

		if (!shapeName.empty()) {

			if (equalsIgnoreCase(shapeName, "box")) bodyDef.shape = PhysicsBody::Shape::Box;

			else if (equalsIgnoreCase(shapeName, "capsule")) bodyDef.shape = PhysicsBody::Shape::Capsule;

			else if (equalsIgnoreCase(shapeName, "circle")) bodyDef.shape = PhysicsBody::Shape::Circle;

		}


	}
}