#pragma once
#include <memory>

namespace viper {
	class Game
	{
	public:
		Game() = default;
		
		virtual bool Initialize() = 0;
		virtual void Shutdown() = 0;
		virtual void Draw(class Renderer& renderer) = 0;
		virtual void Update(float dt) = 0;

		void AddPoints(float points) {m_score += points * multiplier;}
		float getPoints() const {return m_score;}

		void SetLives(int lives) {m_lives = lives;}
		int getLives() const { return m_lives; }

		void increaseMultiplier(float mult) { multiplier += mult; }
		void resetMultiplier(float mult = 1.0f) { multiplier = mult; }


	protected:
		float multiplier{ 1.0f };
		float m_score{ 0 };
		int m_lives{ 0 };
		std::unique_ptr<class Scene> m_scene;
	};
		
}