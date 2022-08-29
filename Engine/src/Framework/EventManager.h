#pragma once
#include "Event.h"
#include <string>
#include <map>
#include <list>

namespace pb {

	class EventManager : public Event{
	public:
		struct Observer {
			GameObject* reciever = nullptr;
			Event::functionPtr function;
		};
	public:
		void Initialize();
		void Shutdown();
		void Update();

		void Subscribe(const std::string& name, Event::functionPtr function, GameObject* reciever = nullptr);
		void Unsubscribe(const std::string& name, GameObject* reciever);

		void Notify(const Event& _event);

	private:
		std::map<std::string, std::list<Observer>> m_events;
	};
}