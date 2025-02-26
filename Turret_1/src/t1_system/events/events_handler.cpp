
#include "events_handler.h"
#include <iostream>


void EventsHandler::pushEvent(t1::EventType type, std::unique_ptr<t1::Event> event)
{
	events[type] = std::move(event);
}

void EventsHandler::clearEvents() noexcept
{
	events.clear();
}

void EventsHandler::pollSimulationEvents()
{
	for (auto& entry : events)
	{
		auto& event = entry.second;
		if (event->active)
		{
			event->active = false;
			//std::cout << " active\n";
		}
			
	}
}


bool EventsHandler::active(const t1::EventType eventType)
{
	const auto& found = events.find(eventType);
	if (found == events.end())
		return false;
	return found->second->active;
}


void EventsHandler::init()
{
	using namespace t1;

	events.emplace(EventType::MAP_CHANGED, std::unique_ptr<MapChanged>());

};
