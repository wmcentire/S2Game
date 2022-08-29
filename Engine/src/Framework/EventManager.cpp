#include "EventManager.h"

namespace pb {
	void EventManager::Initialize()
	{
		//
	}

	void EventManager::Shutdown()
	{
		//
	}

	void EventManager::Update()
	{
		//
	}

	void EventManager::Subscribe(const std::string& name, Event::functionPtr function, GameObject* reciever)
	{
		Observer observer;
		observer.reciever = reciever;
		observer.function = function;

		m_events[name].push_back(observer);
	}

	void EventManager::Unsubscribe(const std::string& name, GameObject* reciever)
	{
		//
	}

	void EventManager::Notify(const Event& _event)
	{
		auto& observers = m_events[_event.name];
		for (auto& observer : observers) {
			if (_event.reciever == nullptr || _event.reciever == observer.reciever) {
				observer.function(_event);
			}
		}
	}
}