#pragma once
#include <box2d/box2d.h>

namespace viper {
	class PhysicsBody {
	public:
		enum class Shape {
			Box,
			Circle,
			Capsule
		};

		struct PhysicsBodyDef {
			// body
			float gravityScale = 1;
			float linearDamping = 0.2f;
			float angularDamping = 0.2f;
			bool  constrainAngle = false;
			bool  isDynamic = true;

			// material
			float friction = 0.3f;
			float restitution = 0.5f;
			float density = 1.0f;

			// shape
			Shape shape = Shape::Box;
			bool isSensor = false;

			class Actor* actor{ nullptr };
		};
	};
}