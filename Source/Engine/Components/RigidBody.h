#pragma once

#include "Game/Component.h"


namespace viper {

	class RigidBody : public Component {
	public:
		float damping{ 0.0f };
		vec2 velocity{ 0.0f, 0.0f }; 
	public:
		CLASS_PROTOTYPE(RigidBody)
		void update(float deltaTime) override;
		void Read(const json::value_t& value);
	};
}