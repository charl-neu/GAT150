#include "GameGame.h"
#include "Math/Vector2.h"
#include "Renderer/Model.h"
#include "Game/Scene.h"
#include "Core/Random.h"
#include "GamePlayer.h"
#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Input/Input System.h"
#include "Enemy.h"
#include "GameData.h"
#include "Renderer/Particle System.h"


#include <vector>


bool SpaceGame::Initialize()
{
	m_scene = std::make_unique<viper::Scene>(this);

	m_titlefont = std::make_shared<viper::Font>();
	m_titlefont->Load("Assets/bsde.ttf", 120.0f);

	m_uifont = std::make_shared<viper::Font>();
	m_uifont->Load("Assets/fonty.ttf", 40.0f);

	m_titleText = std::make_unique<viper::Text>(m_titlefont);
	m_titleText->Create(viper::GetEngine().GetRenderer(), "That One Bad Area.", viper::vec3{ 1.0f, 1.0f, 1.0f });

	m_scoreText = std::make_unique<viper::Text>(m_uifont);
	m_scoreText->Create(viper::GetEngine().GetRenderer(), "Score: 0", viper::vec3{ 1.0f, 1.0f, 1.0f });

	m_livesText = std::make_unique<viper::Text>(m_uifont);
	m_livesText->Create(viper::GetEngine().GetRenderer(), "Lives: 3", viper::vec3{ 1.0f, 1.0f, 1.0f });

	m_healthText = std::make_unique<viper::Text>(m_uifont);
	m_healthText->Create(viper::GetEngine().GetRenderer(), "Health: 3", viper::vec3{ 1.0f, 1.0f, 1.0f });

	m_multText = std::make_unique<viper::Text>(m_uifont);
	m_multText->Create(viper::GetEngine().GetRenderer(), "Multiplier: 100%", viper::vec3{ 1.0f, 1.0f, 1.0f });

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
		std::shared_ptr<viper::Model> pl_model = std::make_shared<viper::Model>(GameData::pl_points, viper::vec3{ 0, 0, 1.0f });

		viper::Transform transform{ viper::vec2{viper::GetEngine().GetRenderer().GetWidth() * .5f,viper::GetEngine().GetRenderer().GetHeight() * .5f}, 0, 5.0f };
		auto player = std::make_unique<Player>(transform, pl_model);
		player->damping = 0.5f;
		player->accel = 400.0f;
		player->angularVel = 240.0f;
		player->name = "Player";  
		player->tag = "player";
		m_scene->AddActor(std::move(player));

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
	if (m_gameState == GameState::Title) {
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

		Player* player = m_scene->GetActorByName<Player>("Player");
		if (player) {
		m_healthText->Create(renderer, "Health: " + std::to_string(m_scene->GetActorByName<Player>("Player")->health), viper::vec3{ 1.0f, 1.0f, 1.0f });
		} else {
			m_healthText->Create(renderer, "Health: 0", viper::vec3{ 1.0f, 1.0f, 1.0f });
		}
		m_healthText->Draw(renderer, (float)renderer.GetWidth() * .01f, (float)renderer.GetHeight() * .09f);
	}

	m_scene->Draw(renderer);

	viper::GetEngine().GetParticleSystem().Draw(renderer);
}

void SpaceGame::OnPlayerDeath()
{
	m_gameState = GameState::PlayerDeath;
	m_stateTimer = 2.0f;
}

void SpaceGame::SpawnEnemy() {
	Player* player = m_scene->GetActorByName<Player>("Player");

	if (player) {
		switch (viper::random::getInt(0, 3)) {
		case 0:
			{
				std::shared_ptr<viper::Model> en_model = std::make_shared<viper::Model>(GameData::sp_points, viper::vec3{ 1.0f, 0, 0 });

				viper::vec2 position = player->transform.position + viper::random::onUnitCircle() * viper::random::getReal(200.0f, 500.0f);
				viper::Transform transform{ position, viper::random::getReal(0.0f, 360.0f), 4.5f };


				std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, en_model);
				enemy->damping = 1.5f;
				enemy->accel = (viper::random::getReal() * 600.0f) + 200.0f;
				enemy->name = "speeder";
				enemy->tag = "enemy";
				enemy->firetimer = 9999999.0f;
				enemy->m_points = 200;
				m_scene->AddActor(std::move(enemy));
			}
				break;
		case 1:
			{
				std::shared_ptr<viper::Model> en_model = std::make_shared<viper::Model>(GameData::ba_points, viper::vec3{ 1.0f, 0, 0 });

				viper::vec2 position = player->transform.position + viper::random::onUnitCircle() * viper::random::getReal(200.0f, 500.0f);
				viper::Transform transform{ position, viper::random::getReal(0.0f, 360.0f), 4.5f };


				std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, en_model);
				enemy->damping = 0.5f;
				enemy->accel = (viper::random::getReal() * 200.0f) + 50.0f;
				enemy->name = "Basic enemy";
				enemy->tag = "enemy";
				m_scene->AddActor(std::move(enemy));
			}
				break;
		case 2:
			{
				std::shared_ptr<viper::Model> en_model = std::make_shared<viper::Model>(GameData::bg_points, viper::vec3{ 1.0f, 0, 0 });

				viper::vec2 position = player->transform.position + viper::random::onUnitCircle() * viper::random::getReal(200.0f, 500.0f);
				viper::Transform transform{ position, viper::random::getReal(0.0f, 360.0f), 4.5f };


				std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, en_model);
				enemy->damping = 1.0f;
				enemy->accel = (viper::random::getReal() * 50.0f) + 10.0f;
				enemy->name = "Big guy";
				enemy->tag = "enemy";
				enemy->m_points = 250;
				enemy->maxfire = 1.0f;
				m_scene->AddActor(std::move(enemy));
			}
				break;
		case 3:
			{
				std::shared_ptr<viper::Model> en_model = std::make_shared<viper::Model>(GameData::bg_points, viper::vec3{ 1.0f, 0, 0 });

				viper::vec2 position = player->transform.position + viper::random::onUnitCircle() * viper::random::getReal(200.0f, 500.0f);
				viper::Transform transform{ position, viper::random::getReal(0.0f, 360.0f), 0.1f };


				std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, en_model);
				enemy->damping = .25f;
				enemy->accel = (viper::random::getReal() * 50.0f) + 10.0f;
				enemy->name = "immortal snail";
				enemy->tag = "enemy";
				enemy->m_points = 500;
				enemy->firetimer = 999999999.0f;
				m_scene->AddActor(std::move(enemy));
			}
			default:
				break;

		}
	}


}
