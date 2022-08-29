#pragma once
#include "Framework/Game.h"

namespace pb {
	class Event;
}

class DesertStormers : public pb::Game {
public:
	enum class gameState {
		title_screen,
		start_level,
		game,
		player_dead,
		game_over,
		boss_fight
	};
public:
	// Inherited via Game
	virtual void Initialize() override;
	virtual void Shutdown() override;
	virtual void Update() override;
	virtual void Draw(pb::Renderer& renderer) override;

	void OnAddPoints(const pb::Event& _event);
	void OnPlayerDead(const pb::Event& _event);

private:
	gameState m_gameState = gameState::title_screen;
	float m_stateTimer = 0;
	int m_health = 0;
};