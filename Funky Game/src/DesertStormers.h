#pragma once
#include "Framework/Game.h"

class DesertStormers : public pb::Game {
public:
	// Inherited via Game
	virtual void Initialize() override;
	virtual void Shutdown() override;
	virtual void Update() override;
	virtual void Draw(pb::Renderer& renderer) override;

private:

};