#pragma once

namespace viper
{
	class ICollidable {
	public:
		virtual ~ICollidable() = default;

		virtual void onCollision(Actor* other) = 0;
	};
}