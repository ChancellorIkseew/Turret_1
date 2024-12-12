#pragma once
#ifndef T1_SYSTEM_EVENTS_HANDLER_H
#define T1_SYSTEM_EVENTS_HANDLER_H

#include <memory>
#include <unordered_map>
#include "t1_events.h"

using EventsMap = std::unordered_map<t1::EventType, std::unique_ptr<t1::Event>>;

class EventsHandler
{
private:
	static inline EventsMap events;

public:
	EventsHandler() = default;
	~EventsHandler() = default;

	static void pushEvent(t1::EventType type, std::unique_ptr<t1::Event> event);
	static void clearEvents() noexcept;
	static void pollSimulationEvents();

	static bool active(const t1::EventType eventType);
	static void init();
};

#endif // T1_SYSTEM_EVENTS_HANDLER_H
