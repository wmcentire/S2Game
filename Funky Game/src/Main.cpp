#include "Engine.h"
#include <iostream>



int main() {


	std::cout << __FILE__ << std::endl;
	std::cout << __LINE__ << std::endl;
	//std::cout << ____ << std::endl;

	pb::InitializeMemory();
	pow_fi::SetFilePath("../Assets");

	//json
	rapidjson::Document document;
	bool success = pb::json::Load("json.txt", document);

	int i1;
	pb::json::Get(document, "integer1", i1);
	std::cout << i1 << std::endl;

	int i2;
	pb::json::Get(document, "integer2", i2);
	std::cout << i2 << std::endl;

	pb::g_audiosystem.Initialize();
	pb::g_inputSystem.Initialize();
	pb::g_renderer.Initialize();
	pb::g_resources.Initialize();

	pb::Engine::Instance().Register();
	
	pb::g_renderer.CreateWindow("Desert Stormers",1000,800);

	pb::Vector2 imageScale;
	imageScale.x = .15f;
	imageScale.y = .15f;
	
	std::shared_ptr<pb::Model> model = pb::g_resources.Get<pb::Model>("models/Player.txt");
	std::shared_ptr<pb::Model> model2 = pb::g_resources.Get<pb::Model>("models/Player.txt");


	//add actors
	pb::Transform transform{ {400, 400}, 0, {1, 1 } };


	std::unique_ptr<pb::Actor> player = std::make_unique<pb::Actor>(transform);
	std::unique_ptr<pb::Component> pComponent = pb::Factory::Instance().Create<pb::PlayerComponent>("PlayerComponent");
	//pComponent->m_transform.scale = imageScale;
	player->AddComponent(std::move(pComponent));
	
	//add audios
	pb::g_audiosystem.AddAudio("Laser","audio/Laser_Galaga.wav");

	//add spriteC
	std::unique_ptr<pb::SpriteComponent> sComponent = std::make_unique<pb::SpriteComponent>();

	std::shared_ptr<pb::Texture> texture = pb::g_resources.Get<pb::Texture>("sprites/C4.png",&pb::g_renderer);
	sComponent->m_texture = texture;
	player->AddComponent(std::move(sComponent));

	//add audioC
	std::unique_ptr<pb::AudioComponent> aComponent = std::make_unique<pb::AudioComponent>();
	aComponent->m_soundname = "Laser";
	player->AddComponent(std::move(aComponent));
	
	//add physicsC
	std::unique_ptr<pb::PhysicsComponent> phComponent = std::make_unique<pb::PhysicsComponent>();
	player->AddComponent(std::move(phComponent));

	//add font
	auto font = pb::g_resources.Get<pb::Font>("fonts/chintzy.ttf", 10);


	pb::Scene scene1;
	scene1.Add(std::move(player));

	bool gameOver = false;
	while (!gameOver) {
		//update
		pb::g_time.Tick();
		pb::g_audiosystem.Update();
		pb::g_inputSystem.Update();
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
