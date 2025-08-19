#pragma once
#include "RendererComponent.h"

namespace viper {

	class SpriteRenderer : public RendererComponent {
	public:
		std::string textureName;

		void update(float deltaTime) override;
		void Draw(Renderer& renderer) override;


		void Read(const json::value_t& value) override;

	};
}