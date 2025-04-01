
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
	for (auto& [eventType, event] : events)
	{
		if (event->active)
			event->active = false;
	}
}

bool EventsHandler::active(const t1::EventType eventType)
{
	return events.count(eventType) && events.at(eventType)->active;
}
