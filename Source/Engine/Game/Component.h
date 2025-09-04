#pragma once
#include "Object.h"

namespace nebula {
	class Component : public Object {
	public:
		class Actor* owner{ nullptr };
	public:
		Component() = default;

		virtual void Start() {}
		virtual void Destroyed() {}
		virtual void Update(float deltaTime) = 0;
	};
}