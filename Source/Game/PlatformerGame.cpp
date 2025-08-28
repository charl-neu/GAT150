#include "PlatformerGame.h"

bool PlatformerGame::Initialize() {
	OBSERVER_ADD(Player_dead);
	OBSERVER_ADD(add_pts);

	m_scene = std::make_unique<viper::Scene>(this);
	m_scene->Load("Scenes/prototype.json");
	m_scene->Load("Scenes/level.json");
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
		SpawnPlayer();
		SpawnEnemy();
		m_gameState = GameState::Game;
		break;
	case PlatformerGame::GameState::Game:
		break;
	case PlatformerGame::GameState::PlayerDeath:
		break;
	case PlatformerGame::GameState::GameEnd:
		break;
	}

	m_scene->Update(viper::GetEngine().GetTime().GetDeltatime());
}
void PlatformerGame::Draw(class viper::Renderer& renderer) {
	m_scene->Draw(renderer);

	viper::GetEngine().GetParticleSystem().Draw(renderer);
}
void PlatformerGame::OnPlayerDeath() {

}
void PlatformerGame::SpawnPlayer() {
	auto player = viper::Instantiate("pplayer");
	m_scene->AddActor(std::move(player), true);
}
void PlatformerGame::OnNotify(const viper::Event& event) {

}

void PlatformerGame::SpawnEnemy() {
	auto enemy = viper::Instantiate("pEnemy");
	m_scene->AddActor(std::move(enemy), true);
}