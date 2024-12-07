#pragma once
#ifndef T1_SYSTEM_EVENT_HANDLER_H
#define T1_SYSTEM_EVENT_HANDLER_H

#include <queue>
#include <variant>
#include "events.h"

namespace t1::system
{
	using EventVariant = std::variant<InputEvent>;

	class EventHandler
	{
	private:
		static inline std::queue<EventVariant> eventsQueue;

	public:
		EventHandler() = default;
		~EventHandler() = default;

		static void pushEvent(EventVariant&& event);
		static void clearEvents() noexcept;
		static void pollEvents();
		static void updateInput(const sf::Event& event);

		static bool active(const KeyName keyName);

	};

}

#endif // T1_SYSTEM_EVENT_HANDLER_H
