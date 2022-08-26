#include "DesertStormers.h"
#include "Engine.h"
#include <vector>

void DesertStormers::Initialize()
{
	m_scene = std::make_unique<pb::Scene>();

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

	for (int i = 0; i < 20; i++) {
		auto actor = pb::Factory::Instance().Create<pb::Actor>("Coin");
		actor->m_transform.position = { pb::randomf(0,800), 100.0f };
		actor->Initialize();

		m_scene->Add(std::move(actor));

	}
}

void DesertStormers::Shutdown()
{
	m_scene->RemoveAll();
}

void DesertStormers::Update()
{
	m_scene->Update();
}

void DesertStormers::Draw(pb::Renderer& renderer)
{
	m_scene->Draw(renderer);
}
