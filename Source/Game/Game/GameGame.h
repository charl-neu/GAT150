#pragma once
#include "Game/Game.h"
#include <memory>
#include "Renderer/Font.h"
#include "Renderer/Text.h"



class SpaceGame : public viper::Game
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
	void Draw(class viper::Renderer& renderer) override;

	void OnPlayerDeath();
	float scoremultiplier = 1.0f;

private:
	void SpawnEnemy();
private:

	GameState m_gameState = GameState::Initialize;
	float m_enemySpawnTimer = 0.0f;
	float m_stateTimer{ 0 };
	
	std::shared_ptr<viper::Font> m_titlefont;
	std::shared_ptr<viper::Font> m_uifont;

	std::unique_ptr<viper::Text> m_titleText;
	std::unique_ptr<viper::Text> m_scoreText;
	std::unique_ptr<viper::Text> m_livesText;
	std::unique_ptr<viper::Text> m_healthText;
	std::unique_ptr<viper::Text> m_multText;
};
