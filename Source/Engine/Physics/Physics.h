#pragma once
#include <box2d/box2d.h>
#include <memory>
#include "../Math/Vector2.h"

namespace viper {
	inline b2Vec2 to_b2(const vec2& v) { return b2Vec2{ v.x, v.y }; }
	inline vec2 to_v2(const b2Vec2& v) { return vec2{ v.x, v.y }; }

	class Physics {
	public:
		Physics() = default;
		bool Initialize();
		void Shutdown();

		void Update(float dt);

		static vec2 WorldToPixel(const vec2& world) { return world * 48.0f; }
		static vec2 PixelToWorld(const vec2& pixel) { return pixel / 48.0f; }

		static void setPixelsPerUnit(float ppu) { ms_pixelsperUnit = ppu; }

		static float ms_pixelsperUnit;

	private:
		b2WorldId m_worldId;
	};
}