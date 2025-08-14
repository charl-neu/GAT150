#pragma once

#include "Game/Component.h"


namespace viper {
	class RigidBody : public Component {
	public:
		float damping{ 0.0f };
		vec2 velocity{ 0.0f, 0.0f }; 
	public:
		void update(float deltaTime) override;

	};
}