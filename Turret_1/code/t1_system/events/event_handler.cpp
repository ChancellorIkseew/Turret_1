
#include "event_handler.h"
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
			std::cout << " active\n";
		}
			
	}
}

void EventsHandler::updateInput(const sf::Event& event)
{
	for (auto& entry : t1::bindings)
	{
		auto& binding = entry.second;

		if (binding.inputType == t1::InputType::keyboard && event.type == sf::Event::KeyPressed)
		{
			binding.active = static_cast<sf::Keyboard::Scancode>(binding.code) == event.key.scancode;
			continue;	// scancode - the code of concrete key
		}

		if (binding.inputType == t1::InputType::mouse && event.type == sf::Event::MouseButtonPressed)
		{
			binding.active = static_cast<sf::Mouse::Button>(binding.code) == event.mouseButton.button;
			continue;
		}

		binding.active = false;
	}
}


bool EventsHandler::active(const t1::KeyName keyName)
{
	const auto& found = t1::bindings.find(keyName);
	if (found == t1::bindings.end())
		return false;
	return found->second.active;
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

	events.emplace(EventType::INPUT_REGISTRED, std::make_unique<InputRegistred>());
	events.emplace(EventType::MAP_CHANGED, std::unique_ptr<MapChanged>());

};
