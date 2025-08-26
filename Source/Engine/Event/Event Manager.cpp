#include "Event Manager.h"
#include "Core/StringHelperr.h"

namespace viper
{
	void EventManager::AddObserver(const Event::id_t& eventId, IObserver& observer)
	{
		m_observers[eventId].push_back(&observer);
	}
	void EventManager::RemoveObserver(IObserver& observer)
	{
		IObserver* obsPtr = &observer;

		for (auto eventType: m_observers) {
			auto& observers = eventType.second;

			std::erase_if(observers, [obsPtr](auto observer) {
				return (observer == obsPtr);
			});
		}
	}

	void EventManager::Notify(const Event& event)
	{
	}
}
