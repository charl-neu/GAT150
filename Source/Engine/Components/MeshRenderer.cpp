#include "MeshRenderer.h"
#include "Renderer/Renderer.h"

namespace viper
{
	void MeshRenderer::update(float deltaTime)
	{
		/*
		if (owner) {
			owner->Update(deltaTime);
		}
		*/
	}

	void MeshRenderer::Draw(Renderer& renderer)
	{
		if (m_mesh.m_points.empty()) return;
		renderer.SetColor(m_mesh.m_color.x, m_mesh.m_color.y, m_mesh.m_color.z, 255);
		m_mesh.Draw(renderer, owner->transform);

	}

}
