#include "PhysicsBody.h"
#include "Physics.h"

namespace nebula {
	PhysicsBody::PhysicsBody(const Transform& transform, const vec2& size, const PhysicsBodyDef& def, const Physics& physics)
	{
		b2BodyDef bodyDef = b2DefaultBodyDef();

		// set body definition
		bodyDef.type = (def.isDynamic) ? b2_dynamicBody : b2_staticBody;
		bodyDef.position = to_b2(Physics::PixelToWorld(transform.position));
		bodyDef.rotation = b2MakeRot(DegToRad(transform.rotation));
		bodyDef.motionLocks.angularZ = def.constrainAngle;
		bodyDef.gravityScale = def.gravityScale;
		bodyDef.linearDamping = def.linearDamping;
		bodyDef.angularDamping = def.angularDamping;
		bodyDef.userData = def.actor;

		// create body
		m_bodyid = b2CreateBody(physics.m_worldId, &bodyDef);

		// set shape definition
		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeDef.material.friction = def.friction;
		shapeDef.material.restitution = def.restitution;
		shapeDef.density = def.density;
		shapeDef.isSensor = def.isSensor;

		if (def.isSensor) shapeDef.enableSensorEvents = true;
		else shapeDef.enableContactEvents = true;

		// create shape
		b2Vec2 hsize = to_b2(Physics::PixelToWorld(size * transform.scale * 0.5f));
		switch (def.shape)
		{
		case Shape::Box:
		{
			b2Polygon box = b2MakeBox(hsize.x, hsize.y);
			b2CreatePolygonShape(m_bodyid, &shapeDef, &box);
		}
		break;
		case Shape::Capsule:
		{
			b2Capsule capsule{ b2Vec2{ 0, hsize.y - hsize.x }, b2Vec2{ 0, -(hsize.y - hsize.x) }, hsize.x };
			b2CreateCapsuleShape(m_bodyid, &shapeDef, &capsule);
		}
		break;
		case Shape::Circle:
		{
			b2Circle circle{ b2Vec2{ 0, 0 }, hsize.x };
			b2CreateCircleShape(m_bodyid, &shapeDef, &circle);
		}
		break;
		default:
			break;
		}
	}
	PhysicsBody::~PhysicsBody()
	{
		b2DestroyBody(m_bodyid);
	}
	vec2 PhysicsBody::GetPosition()
	{
		return Physics::WorldToPixel(to_v2(b2Body_GetPosition(m_bodyid)));
	}
	float PhysicsBody::GetAngle()
	{
		return b2Rot_GetAngle(b2Body_GetRotation(m_bodyid));
	}
	void PhysicsBody::applyForce(const vec2& force)
	{
		b2Body_ApplyForceToCenter(m_bodyid, to_b2(Physics::PixelToWorld(force)), true);
	}
	void PhysicsBody::applyTorque(float radians)
	{
		b2Body_ApplyTorque(m_bodyid, radians, true);
	}
	void PhysicsBody::setVelocity(const vec2& velocity)
	{
		b2Body_SetLinearVelocity(m_bodyid, to_b2(Physics::PixelToWorld(velocity)));
	}
	vec2 PhysicsBody::Getvelocity()
	{
		return Physics::WorldToPixel(to_v2(b2Body_GetLinearVelocity(m_bodyid)));
	}
}