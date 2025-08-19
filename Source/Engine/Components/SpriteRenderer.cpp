#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"


namespace viper
{
	FACTORY_REGISTER(SpriteRenderer)

	void SpriteRenderer::update(float deltaTime)
	{

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

	void SpriteRenderer::Read(const json::value_t& value)
	{
		Object::Read(value);

		JSON_READ(value, textureName);
	}

}
