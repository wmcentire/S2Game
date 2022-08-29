#include "Scene.h"
#include "Actor.h"
#include "Factory.h"
#include <iostream>

namespace pb {
	void Scene::Update()
	{
		auto iter = m_actors.begin();

		while (iter != m_actors.end()) {
			(*iter)->Update();
			//Extra update for extra fast
			if ((*iter)->m_destroy){
				iter = m_actors.erase(iter);
			}
			else {
				iter++;
			}
		}
		
		

		/*
		for (auto& actor : m_actors) { 
			actor->Update();
		}*/
	}

	void Scene::Draw(Renderer& renderer)
	{
		for (auto& actor : m_actors) {
			actor->Draw(renderer);
		}
	}

	void Scene::Add(std::unique_ptr<Actor> actor) {
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
	}
	void Scene::Initialize()
	{
		for (auto& actor : m_actors) {
			actor->Initialize();
		}
	}
	void Scene::RemoveAll()
	{
		for (auto& actor : m_actors)
		m_actors.clear();
	}
	bool Scene::Write(const rapidjson::Value& value) const
	{
		return true;
	}
	bool Scene::Read(const rapidjson::Value& value)
	{
		if (!value.HasMember("actors") || !value["actors"].IsArray()) {
			return false;
		}
		for (auto& actorValue : value["actors"].GetArray()) {
			std::string type;
			READ_DATA(actorValue, type);

			auto actor = Factory::Instance().Create<Actor>(type);
			if (actor) {
				actor->Read(actorValue);
				
				bool prefab = false;
				READ_DATA(actorValue, prefab);

				if (prefab) {
					std::string name = actor->GetName();
					Factory::Instance().RegisterPrefab(name, std::move(actor));
				}
				else {
					Add(std::move(actor));
				}
			}
		}
		return true;
	}
}