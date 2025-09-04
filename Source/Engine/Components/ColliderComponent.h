#pragma once
#include "Game/Component.h"

namespace nebula
{
	class ColliderComponent : public Component
	{
	public:
		virtual bool CheckCollision(const ColliderComponent& other) const = 0;
	};
}