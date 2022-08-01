#pragma once
#include <memory>


namespace pb {

	class Renderer;
	class Scene;

	class Game{
		//abstract ideas lol
	public:
		Game() = default;
		virtual ~Game() = default;

		virtual void Initialize() = 0;
		virtual void Shutdown() = 0;

		virtual void Update() = 0;
		virtual void Draw(pb::Renderer& renderer) = 0;

		int GetScore() { return m_score; }
		void AddPoints(int points) { m_score += points; }

		int GetTime() { return m_time; }
		void Addtime(int time) { m_time += time; }

	protected:
		std::unique_ptr<Scene> m_scene;
		int m_score = 0;
		int m_time = 0;
		int m_hScore = 0;
		int m_hTime = 0;
	};
}