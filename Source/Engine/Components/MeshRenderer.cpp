#include "MeshRenderer.h"
#include "Renderer/Renderer.h"
#include "Resources/ResourceManager.h"
#include "Game/Actor.h"


namespace viper
{
	FACTORY_REGISTER(MeshRenderer)

	void MeshRenderer::update(float deltaTime)
	{

	}

	void MeshRenderer::Draw(Renderer& renderer)
	{ 

		auto mesh = Resources().Get<Mesh>(meshName).get();
		if (mesh) {
			mesh->Draw(renderer, owner->transform);
		}
		else {
			Logger::Error("Mesh not found: {}", meshName);
		}
		
	}

}
