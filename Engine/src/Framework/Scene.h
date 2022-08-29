#pragma once
#include "Serialization/Serializable.h"
#include "GameObject.h"
#include <string>
#include <list>
#include <memory>

namespace pb {

	class Actor;
	class Renderer;
	class Game;
	class Scene : public GameObject, public ISerializable
	{
	public:
		Scene() = default;
		Scene(const Scene& other) {}
		Scene(Game* game) : m_game{game}{}
		~Scene() = default;
		CLASS_DECLARATION(Scene)
		void Update();
		void Draw(Renderer& renderer);
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Add(std::unique_ptr<Actor> actor);
		virtual void Initialize() override;
		void RemoveAll();

		template<typename T>
		T* GetActor();

		template<typename T = Actor>
		T* GetActorFromName(const std::string& name);

		template<typename T = Actor>
		std::vector<T*> GetActorsFromTag(const std::string& tag);

		Game* GetGame() { return m_game; }

	private:
		std::list<std::unique_ptr<Actor>> m_actors;
		Game* m_game;


		
	};
	template<typename T>
	inline T* Scene::GetActor()
	{
		for (auto& actor : m_actors) {

			T* result = dynamic_cast<T*>(actor.get());
			if (result) {
				return result;
			}
		}

		return nullptr;
	}

	template<typename T>
	inline T* Scene::GetActorFromName(const std::string& name)
	{
		 
		for(auto& actor : m_actors) {
			if (actor.get()->GetName() == name) 
				{
				 return dynamic_cast<T*>(actor.get()); 
				}
		}

		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Scene::GetActorsFromTag(const std::string& tag)
	{
		std::vector<T*> result;

		//  !! for loop (range based) through m_actors 
		for (auto actor : m_actors) {
			if (actor->GetTag() == tag) {
				T* tagActor = dynamic_cast<T*>(actor.get()); //  !! get() actor pointer); 
				if (tagActor) {
					result.push_back(tagActor);
				}//  !! push back tagActor to result vector 
			}

		}
		return result;
	}
}
