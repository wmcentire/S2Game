#include "Engine.h"
#include "DesertStormers.h"
#include <iostream>



int main() {


	std::cout << __FILE__ << std::endl;
	std::cout << __LINE__ << std::endl;
	//std::cout << ____ << std::endl;

	pb::InitializeMemory();
	pow_fi::SetFilePath("../Assets");

	//json
	
	

	pb::g_audiosystem.Initialize();
	pb::g_inputSystem.Initialize();
	pb::g_renderer.Initialize();
	pb::g_resources.Initialize();
	pb::g_physicssystem.Initialize();

	pb::Engine::Instance().Register();
	
	pb::g_renderer.CreateWindow("Desert Stormers",1000,800);

	std::unique_ptr<DesertStormers> game = std::make_unique<DesertStormers>();
	
	game->Initialize();

	
	bool gameOver = false;
	while (!gameOver) {
		//update
		pb::g_time.Tick();
		pb::g_audiosystem.Update();
		pb::g_inputSystem.Update();
		pb::g_physicssystem.Update();
		game->Update();
		//exit
		if (pb::g_inputSystem.GetKeyDown(pb::C_key_escape)) {
			gameOver = true;
		}

		pb::g_renderer.BeginFrame();
		//texture
		
		game->Draw(pb::g_renderer);

		pb::g_renderer.EndFrame();

	}
	game->Shutdown();
	game.reset();
	pb::Factory::Instance().ShutDown();

	pb::g_renderer.Shutdown();
	pb::g_audiosystem.Shutdown();
	pb::g_inputSystem.Shutdown();

}
