#include "PlatformerGame.h"
#include "PlayerController.h"

bool PlatformerGame::Initialize() {
	OBSERVER_ADD(Player_dead);

	m_scene = std::make_unique<nebula::Scene>(this);
	m_scene->Load("Scenes/prototype.json");
	m_scene->Load("Scenes/level.json");

	m_titleText = std::make_unique<nebula::Text>(nebula::Resources().GetWithID<nebula::Font>("Title_font", "bsde.ttf", 120.0f));
	m_scoreText = std::make_unique<nebula::Text>(nebula::Resources().GetWithID<nebula::Font>("UI_font", "fonty.ttf", 40.0f));
	m_healthText = std::make_unique<nebula::Text>(nebula::Resources().GetWithID<nebula::Font>("UI_font", "fonty.ttf", 40.0f));
	return true;
}
void PlatformerGame::Shutdown() {
	//
}
void PlatformerGame::Update(float dt) {
	switch (m_gameState)
	{
	case PlatformerGame::GameState::Initialize:
		m_gameState = GameState::StartRound;
		break;
	case PlatformerGame::GameState::Title:
		break;
	case PlatformerGame::GameState::StartGame:
		break;
	case PlatformerGame::GameState::StartRound:
		
		m_scene->RemoveAllActors(false);
		
		SpawnPlayer();
		SpawnEnemy();
		m_gameState = GameState::Game;
		break;
	case PlatformerGame::GameState::Game:
		AddPoints(100 * dt);
		m_enemySpawnTimer -= dt;
		if (m_enemySpawnTimer <= 0.0f) {
			m_enemySpawnTimer = nebula::random::getReal() * 5.0f + 2.5f; 
			SpawnEnemy();
		}
		break;
	case PlatformerGame::GameState::PlayerDeath:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0.0f) {
			
			m_gameState = GameState::GameEnd;
			m_stateTimer = 3.0f;
			
		}
		break;
	case PlatformerGame::GameState::GameEnd:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0.0f) {
			m_gameState = GameState::Initialize;
			m_score = 0; 
		}
		break;
	}

	m_scene->Update(nebula::GetEngine().GetTime().GetDeltatime());
}
void PlatformerGame::Draw(class nebula::Renderer& renderer) {
	m_scene->Draw(renderer);

	if (m_gameState == GameState::GameEnd) {
		m_titleText->Create(renderer, "Game Over", nebula::vec3{ 1.0f, 0.0f, 0.0f });
		m_titleText->Draw(renderer, (float)renderer.GetWidth() * .3f, (float)renderer.GetHeight() * .1f);
	}
	
	if (m_gameState == GameState::Game || m_gameState == GameState::StartRound || m_gameState == GameState::PlayerDeath) {
		int truncscore = nebula::trunc(m_score);
		m_scoreText->Create(renderer, "Score: " + std::to_string(truncscore), nebula::vec3{ 1.0f, 1.0f, 1.0f });
		m_scoreText->Draw(renderer, (float)renderer.GetWidth() * .01f, (float)renderer.GetHeight() * .01f);

		auto actor = m_scene->GetActorByName<nebula::Actor>("pPlayer");
		PlayerController* player = nullptr;
		if (actor) {
			player = actor->GetComponent<PlayerController>();
		}

		if (player) {
			m_healthText->Create(renderer, "Health: " + std::to_string(player->health), nebula::vec3{ 1.0f, 1.0f, 1.0f });
		}
		else {
			m_healthText->Create(renderer, "Health: 0", nebula::vec3{ 1.0f, 1.0f, 1.0f });
		}

		m_healthText->Draw(renderer, (float)renderer.GetWidth() * .01f, (float)renderer.GetHeight() * .09f);
	}
	

	nebula::GetEngine().GetParticleSystem().Draw(renderer);
}
void PlatformerGame::OnPlayerDeath() {
	m_gameState = GameState::PlayerDeath;
	m_stateTimer = 2.0f;
}
void PlatformerGame::SpawnPlayer() {
	auto player = nebula::Instantiate("pplayer");
	m_scene->AddActor(std::move(player), true);
}
void PlatformerGame::OnNotify(const nebula::Event& event) {
	if (event.id == "Player_dead") {
		OnPlayerDeath();
	}
}

void PlatformerGame::SpawnEnemy() {
	auto enemy = nebula::Instantiate("bat");
	m_scene->AddActor(std::move(enemy), true);
}