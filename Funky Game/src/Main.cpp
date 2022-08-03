#include "Engine.h"
#include <iostream>

int main() {
	pb::InitializeMemory();
	pow_fi::SetFilePath("../Assets");

	pb::g_audiosystem.Initialize();
	pb::g_inputSystem.Initialize();
	pb::g_renderer.Initialize();
	
	pb::g_renderer.CreateWindow("Desert Stormers",1000,800);

	std::shared_ptr<pb::Texture> texture = std::make_shared<pb::Texture>();
	texture->Create(pb::g_renderer, "sf2.bmp");

	bool gameOver = false;
	while (!gameOver) {
		//update
		pb::g_time.Tick();
		pb::g_audiosystem.Update();
		pb::g_inputSystem.Update();
		//exit
		if (pb::g_inputSystem.GetKeyDown(pb::C_key_escape)) {
			gameOver = true;
		}

		pb::g_renderer.BeginFrame();

		//texture
		pb::g_renderer.Draw(texture, { 500, 400 }, 0);

		pb::g_renderer.EndFrame();

	}
	pb::g_renderer.Shutdown();
	pb::g_audiosystem.Shutdown();
	pb::g_inputSystem.Shutdown();

}
