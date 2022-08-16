#include "Scene.h"
#include "Actor.h"
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
		
		//check collision
		for (auto iter1 = m_actors.begin(); iter1 != m_actors.end(); iter1++) {
			for (auto iter2 = m_actors.begin(); iter2 != m_actors.end(); iter2++) {
				if (iter1 == iter2) 
					continue;
				//now the collision math
				float radius = (*iter1)->GetRadius() + (*iter2)->GetRadius();
				float distance = (*iter1)->m_transform.position.Distance( (*iter2)->m_transform.position);
				if (distance < radius) {
					//COLIDES
					(*iter1)->OnCollision((*iter2).get());
					(*iter2)->OnCollision((*iter1).get());
				}
				else {
					//DOES NOT COLIDE
				}
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
}