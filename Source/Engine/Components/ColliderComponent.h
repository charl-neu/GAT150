#pragma once
#include "Game/Component.h"

namespace viper
{
	class ColliderComponent : public Component
	{
	public:
		virtual bool CheckCollision(const ColliderComponent& other) const = 0;
	};
}