#pragma once
#include "RendererComponent.h"


namespace viper {

	class SpriteRenderer : public RendererComponent {
	public:
		std::string textureName;
		res_t<Texture> texture;
		rect textureRect;
		bool fliph = false;

		CLASS_PROTOTYPE(SpriteRenderer)

		void Start() override;
		void Update(float deltaTime) override;
		void Draw(Renderer& renderer) override;


		void Read(const json::value_t& value) override;

	};
}