#pragma once


namespace viper {
	class ParticleSystem
	{
		ParticleSystem() = default;

		bool Initialize();
		void Shutdown();

		void Update(float deltaTime);
		void Draw(class Renderer& renderer);


	}
}