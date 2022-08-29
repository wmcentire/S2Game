#include "DesertStormers.h"
#include "Engine.h"
#include <vector>

void DesertStormers::Initialize()
{
	m_scene = std::make_unique<pb::Scene>();

	//read levels
	rapidjson::Document document;

	std::vector<std::string> sceneNames = { "scenes/prefabs.txt","scenes/Tilemap.txt", "scenes/level.txt" };

	for (auto sceneName : sceneNames) {

		bool success = pb::json::Load(sceneName, document);
		if (!success) {
			LOG("Could Not load scene %s", sceneName.c_str());

			continue;
		}
		m_scene->Read(document);
	}
	m_scene->Initialize();

	
	pb::g_eventManager.Subscribe("EVENT_ADD_POINTS", std::bind(&DesertStormers::OnAddPoints,this,std::placeholders::_1));
}

void DesertStormers::Shutdown()
{
	m_scene->RemoveAll();
}

void DesertStormers::Update()
{
	switch (m_gameState) {
	case gameState::title_screen:
		if (pb::g_inputSystem.GetKeyState(pb::C_key_space) == pb::InputSystem::PRESSED) {

			m_scene->GetActorFromName("Title")->SetActive(false);

			m_gameState == gameState::start_level;

			m_health = 3;
		}
		break;
	case gameState::start_level:
		for (int i = 0; i < 20; i++) {
			auto actor = pb::Factory::Instance().Create<pb::Actor>("Coin");
			actor->m_transform.position = { pb::randomf(0,800), 100.0f };
			actor->Initialize();

			m_scene->Add(std::move(actor));

		}
		break;
	case gameState::player_dead:
		m_stateTimer -= pb::g_time.deltaTime;
		if (m_stateTimer <= 0) {
			m_gameState = gameState::start_level;
		}
		break;
	}
	m_scene->Update();

}

void DesertStormers::Draw(pb::Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void DesertStormers::OnAddPoints(const pb::Event& _event)
{
	AddPoints(std::get<int>(_event.data));

	std::cout << _event.name << std::endl;
	std::cout << std::get<int>(_event.data) << std::endl;
	std::cout << GetScore() << std::endl;
	
}

void DesertStormers::OnPlayerDead(const pb::Event& _event)
{
	m_gameState = gameState::player_dead;
	//m_lives--;
	//a possibility?
	m_stateTimer = 3.0f;

}
