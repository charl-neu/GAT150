#pragma once
#include "Object.h"

namespace viper {
	class Component : public Object {
	public:
		class Actor* owner{ nullptr };
	public:
		Component() = default;
		virtual void update(float deltaTime) = 0;
	};
}