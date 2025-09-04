#include "Event Manager.h"
#include "Core/StringHelperr.h"
#include "Core/Logger.h"



namespace nebula
{
	void EventManager::AddObserver(const Event::id_t& eventId, IObserver& observer)
	{
		m_observers[toLower(eventId)].push_back(&observer);
	}
	void EventManager::RemoveObserver(IObserver& observer)
	{
		IObserver* obsPtr = &observer;

		for (auto& eventType: m_observers) {
			auto& observers = eventType.second;

			std::erase_if(observers, [obsPtr](auto observer) {
				return (observer == obsPtr);
			});
		}
	}

	void EventManager::Notify(const Event& event)
	{
		auto it = m_observers.find(toLower(event.id));
		if (it != m_observers.end()) {
			auto& observers = it->second;
			for (auto& observer : observers) {
				observer->OnNotify(event);
			}
		}
		else {
			Logger::Warning("Could not find event {}", event.id);
		}
	}
	void EventManager::RemoveAll()
	{
		m_observers.clear();
	}
}
