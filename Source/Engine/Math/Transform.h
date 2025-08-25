#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "../Core/Serializable.h"
#include <vector>

namespace viper
{
	struct Transform : public ISerializable
	{
		vec2 position{ 0, 0 };
		float rotation{ 0 }; 
		float scale{ 1 };

		Transform(const vec2& pos = { 0,0 }, float rot = 0, float scl = 1) : position(pos), rotation(rot), scale(scl) {}
		

		void Read(const json::value_t& value) override;
	};
}
