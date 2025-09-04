#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Engine.h"

namespace nebula
{
	FACTORY_REGISTER(SpriteRenderer)

	void SpriteRenderer::Start()
	{
		if (!texture && !textureName.empty()) {
		texture = Resources().Get<Texture>(textureName, GetEngine().GetRenderer());
		}
	}

	void SpriteRenderer::Update(float deltaTime)
	{

	}

	void SpriteRenderer::Draw(Renderer& renderer) {
		if (texture) {
			if (textureRect.w > 0 && textureRect.h > 0) {
				renderer.DrawTexture(*texture,
					textureRect,
					owner->transform.position.x,
					owner->transform.position.y,
					owner->transform.rotation,
					owner->transform.scale,
					fliph);
			}
			else {
				renderer.DrawTextureRotated(*texture,
					owner->transform.position.x,
					owner->transform.position.y,
					owner->transform.rotation,
					owner->transform.scale,
					fliph);
			}
		}
	}

	void SpriteRenderer::Read(const json::value_t& value)
	{
		Object::Read(value);

		JSON_READ(value, textureName);
		JSON_READ(value, fliph);
	}

}
