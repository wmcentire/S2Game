#include "Engine.h"
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

	
	//add audios
	pb::g_audiosystem.AddAudio("Laser","audio/Laser_Galaga.wav");

	

	//add font
	auto font = pb::g_resources.Get<pb::Font>("fonts/chintzy.ttf", 10);


	pb::Scene scene1;

	rapidjson::Document document;
	bool success = pb::json::Load("level.txt", document);

	scene1.Read(document);
	scene1.Initialize();

	auto actor = pb::Factory::Instance().Create<pb::Actor>("Coin");

	bool gameOver = false;
	while (!gameOver) {
		//update
		pb::g_time.Tick();
		pb::g_audiosystem.Update();
		pb::g_inputSystem.Update();
		pb::g_physicssystem.Update();
		scene1.Update();
		//exit
		if (pb::g_inputSystem.GetKeyDown(pb::C_key_escape)) {
			gameOver = true;
		}

		pb::g_renderer.BeginFrame();
		//texture
		
		scene1.Draw(pb::g_renderer);

		pb::g_renderer.EndFrame();

	}
	pb::g_renderer.Shutdown();
	pb::g_audiosystem.Shutdown();
	pb::g_inputSystem.Shutdown();

}
