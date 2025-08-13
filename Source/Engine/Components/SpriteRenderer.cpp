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
		if (owner) {
			renderer.DrawTextureRotated(Resources().Get<Texture>(textureName, renderer).get(),
				owner->transform.position.x,
				owner->transform.position.y,
				owner->transform.scale,
				owner->transform.rotation);
		}
	}

}
