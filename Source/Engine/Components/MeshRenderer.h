#pragma once
#include "Renderer/Mesh.h"
#include "RendererComponent.h"

namespace viper {
	class MeshRenderer : public RendererComponent {
	public:
		Mesh m_mesh;

		void update(float deltaTime) override;
		void Draw(Renderer& renderer) override;

	};
}