#pragma once
#include "Game/Game.h"
#include <memory>
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Event/Observer.h"



class SpaceGame : public nebula::Game, public nebula::IObserver
{
public:
	enum class GameState
	{
		Initialize,
		Title,
		StartGame,
		StartRound,
		Game,
		PlayerDeath,
		GameEnd,
	};

public:
	SpaceGame() = default;
	bool Initialize() override;
	void Shutdown() override;
	void Update(float dt) override;
	void Draw(class nebula::Renderer& renderer) override;

	void OnPlayerDeath();
	float scoremultiplier = 1.0f;

private:
	void SpawnEnemy();
private:

	GameState m_gameState = GameState::Initialize;
	float m_enemySpawnTimer = 0.0f;
	float m_stateTimer{ 0 };
	
	std::shared_ptr<nebula::Font> m_titlefont;
	std::shared_ptr<nebula::Font> m_uifont;

	std::unique_ptr<nebula::Text> m_titleText;
	std::unique_ptr<nebula::Text> m_scoreText;
	std::unique_ptr<nebula::Text> m_livesText;
	std::unique_ptr<nebula::Text> m_healthText;
	std::unique_ptr<nebula::Text> m_multText;

	// Inherited via IObserver
	void OnNotify(const nebula::Event& event) override;
};
