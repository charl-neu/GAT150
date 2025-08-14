#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"

namespace viper
{
	void SpriteRenderer::update(float deltaTime)
	{
		/*
		if (owner) {
			owner->Update(deltaTime);
		}
		*/
	}

	void SpriteRenderer::Draw(Renderer& renderer)
	{ 
		auto texture = Resources().Get<Texture>(textureName, renderer).get();
		if (texture) {
			renderer.DrawTextureRotated(*texture,
				owner->transform.position.x,
				owner->transform.position.y,
				owner->transform.scale,
				owner->transform.rotation);
		}
	}

}
