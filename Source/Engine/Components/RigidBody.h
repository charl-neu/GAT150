#pragma once

#include "Game/Component.h"
#include "../Physics/PhysicsBody.h"

namespace viper {

	class RigidBody : public Component {
	public:
		PhysicsBody::PhysicsBodyDef bodyDef;
		vec2 size{ 0, 0 };
		vec2 scale{ 1,1 };

		float damping{ 0.0f };
		vec2 velocity{ 0.0f, 0.0f }; 
	public:
		RigidBody() = default;
		RigidBody(const RigidBody& other);


		CLASS_PROTOTYPE(RigidBody)
		void Start();
		void Update(float deltaTime) override;
		void Read(const json::value_t& value);

		void applyForce(const vec2& force);
		void applyTorque(float radians);

		void setVelocity(const vec2& velocity);
	private:
		std::unique_ptr<PhysicsBody> m_physicsbody;
	};
}