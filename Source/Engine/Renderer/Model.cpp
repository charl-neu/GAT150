#include "Model.h"
#include "Renderer.h"


namespace viper{

	/// <summary>
	/// Draws the model by rendering lines between its points using the specified renderer.
	/// </summary>
	/// <param name="renderer">The Renderer object used to draw the model.</param>
	void Model::Draw(Renderer& renderer, const vec2& position, float rotation, float scale)
	{
		if (m_points.empty()) return;

		renderer.SetColor(m_color.x, m_color.y, m_color.z, 255);
		for (int i = 0; i < m_points.size()-1; i++)
		{
			vec2 p1 = (m_points[i].Rotate(viper::DegToRad(rotation)) * scale) + position;
			vec2 p2 = (m_points[i + 1].Rotate(viper::DegToRad(rotation)) * scale) + position;

			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	/// <summary>
	/// Draws the model using the specified renderer and transformation.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the model.</param>
	/// <param name="transform">The transformation to apply, including position, rotation, and scale.</param>
	void Model::Draw(Renderer& renderer, const Transform& transform)
	{
		Draw(renderer, transform.position, transform.rotation, transform.scale);
	}

	/// <summary>
	/// Calculates the radius of the model based on its points.
	/// </summary>
	void Model::CalculateRadius()
	{
		
		m_radius = 0.0f;
		for (const auto& point : m_points) {
			float distance = point.Length();
			if (distance > m_radius) {
				m_radius = distance;
			}
		}
	}
}