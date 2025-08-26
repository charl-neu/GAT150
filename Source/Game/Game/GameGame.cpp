#include "GameGame.h"
#include "GamePlayer.h"
#include "Enemy.h"
#include "GameData.h"
#include "../../Engine/Game/Scene.h"


#include <vector>


bool SpaceGame::Initialize()
{
	m_scene = std::make_unique<viper::Scene>(this);
	m_scene->Load("Scene.json");

	m_titleText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("Title_font", "bsde.ttf", 120.0f));
	m_scoreText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("UI_font", "fonty.ttf", 40.0f));
	m_livesText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("UI_font", "fonty.ttf", 40.0f));
	m_healthText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("UI_font", "fonty.ttf", 40.0f));
	m_multText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("UI_font", "fonty.ttf", 40.0f));

	return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{
	m_scene->Update(viper::GetEngine().GetTime().GetDeltatime());
	switch (m_gameState)
	{
	case GameState::Initialize:
		m_gameState = GameState::Title;
		break;
	case GameState::Title:
		if (viper::GetEngine().GetInputSystem().GetKeyPressed(SDL_SCANCODE_SPACE)) {
			m_gameState = GameState::StartGame;
		}
		break;
	case GameState::StartGame:
		{
		m_scene->RemoveAllActors();
		m_lives = 3;
		m_gameState = GameState::StartRound;
		}
		break;
	case GameState::StartRound:
	{
		m_scene->RemoveAllActors();

		//instantiate player at the center of the screen

		viper::Transform transform;
		transform.position = viper::vec2{ viper::GetEngine().GetRenderer().GetWidth() / 2.0f, viper::GetEngine().GetRenderer().GetHeight() / 2.0f };
		auto player = viper::Instantiate("Player", transform);
		//put player in the center of the screen
		
		m_scene->AddActor(std::move(player), true);
		


		m_gameState = GameState::Game;
	}
		break;
	case GameState::Game:
		m_enemySpawnTimer -= dt;
		if (m_enemySpawnTimer <= 0.0f) {
			m_enemySpawnTimer = viper::random::getReal() * 2.0f + 1.0f; // Random spawn time between 1 and 3 seconds
			SpawnEnemy();
		}
		break;
	case GameState::PlayerDeath:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0.0f) {
			m_lives--;
			if (m_lives <= 0) {
				m_gameState = GameState::GameEnd;
				m_stateTimer = 3.0f; 
			}
			else {
				m_gameState = GameState::StartRound;
			}
		}

		break;
	case GameState::GameEnd:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0.0f) {
			m_gameState = GameState::Title;
			m_score = 0; // Reset score
		}
		break;
	default:
		break;
	}
}

void SpaceGame::Draw(viper::Renderer& renderer)
{
	m_scene->Draw(renderer);
	if (m_gameState == GameState::Title) {
		m_titleText->Create(renderer, "That One Bad Area", viper::vec3{ 1.0f, 1.0f, 1.0f });
		m_titleText->Draw(renderer, (float)renderer.GetWidth() * .125f, (float)renderer.GetHeight() * .1f);
	}

	if (m_gameState == GameState::GameEnd) {
		m_titleText->Create(renderer, "Game Over", viper::vec3{ 1.0f, 0.0f, 0.0f });
		m_titleText->Draw(renderer, (float)renderer.GetWidth() * .3f, (float)renderer.GetHeight() * .1f);
	}
	
	if (m_gameState == GameState::Game || m_gameState == GameState::StartRound || m_gameState == GameState::PlayerDeath) {
		int truncscore = viper::trunc(m_score);
		m_scoreText->Create(renderer, "Score: " + std::to_string(truncscore), viper::vec3{ 1.0f, 1.0f, 1.0f });
		m_scoreText->Draw(renderer, (float)renderer.GetWidth() * .01f, (float)renderer.GetHeight() * .01f);

		m_livesText->Create(renderer, "Lives: " + std::to_string(m_lives), viper::vec3{ 1.0f, 1.0f, 1.0f });
		m_livesText->Draw(renderer, (float)renderer.GetWidth() * .01f, (float)renderer.GetHeight() * .05f);

		int truncplier = viper::trunc(multiplier * 100);
		m_multText->Create(renderer, "Multiplier: " + std::to_string(truncplier) + "%", viper::vec3{1.0f, 1.0f, 1.0f});
		m_multText->Draw(renderer, (float)renderer.GetWidth() * .01f, (float)renderer.GetHeight() * .13f);

		
		auto actor = m_scene->GetActorByName<viper::Actor>("Player");
		Player* player = nullptr;
		if (actor) {
			player = actor->GetComponent<Player>();
		}

		if (player) {
			m_healthText->Create(renderer, "Health: " + std::to_string(player->health), viper::vec3{ 1.0f, 1.0f, 1.0f });
		} else {
			m_healthText->Create(renderer, "Health: 0", viper::vec3{ 1.0f, 1.0f, 1.0f });
		}

		m_healthText->Draw(renderer, (float)renderer.GetWidth() * .01f, (float)renderer.GetHeight() * .09f);
	}


	viper::GetEngine().GetParticleSystem().Draw(renderer);
}

void SpaceGame::OnPlayerDeath()
{
	m_gameState = GameState::PlayerDeath;
	m_stateTimer = 2.0f;
}

void SpaceGame::SpawnEnemy() {
	viper::Actor* player = m_scene->GetActorByName<viper::Actor>("Player");
	if (!player) {
		return; // No player found, do not spawn enemies
	}

	viper::vec2 playerPosition = player->transform.position;
	viper::vec2 spawnPosition = playerPosition + viper::random::onUnitCircle() * viper::random::getReal(200.0f, 500.0f);
	switch (viper::random::getInt(0, 3)) {
	case 0:
	{
		//normal enemy
		viper::Transform transform{ spawnPosition, viper::random::getReal(0.0f, 360.0f), 1.5f };
		auto enemy = viper::Instantiate("BEnemy", transform);
		m_scene->AddActor(std::move(enemy), true);
		break;
	}
	case 1:
	{
		//speeder
		viper::Transform transform{ spawnPosition, viper::random::getReal(0.0f, 360.0f), 1.5f };
		auto enemy = viper::Instantiate("SEnemy", transform);
		m_scene->AddActor(std::move(enemy), true);
		break;
	}
	case 2:
	{
		//tank
		viper::Transform transform{ spawnPosition, viper::random::getReal(0.0f, 360.0f), 3.5f };
		auto enemy = viper::Instantiate("TEnemy", transform);
		m_scene->AddActor(std::move(enemy), true);
		break;
	}
	case 3:
	{
		//snail
		viper::Transform transform{ spawnPosition, viper::random::getReal(0.0f, 360.0f), 0.5f };
		auto enemy = viper::Instantiate("IEnemy", transform);
		m_scene->AddActor(std::move(enemy), true);
		break;
	}
	default:
		break;
	}


}
