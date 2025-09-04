#pragma once
#include "Renderer/Mesh.h"
#include "RendererComponent.h"

namespace nebula {

	class MeshRenderer : public RendererComponent {
	public:
		std::string meshName;
		CLASS_PROTOTYPE(MeshRenderer)

		void Update(float deltaTime) override;
		void Draw(Renderer& renderer) override;

	};
}