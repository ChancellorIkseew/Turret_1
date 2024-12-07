
#include "event_handler.h"
#include <iostream>

using namespace t1::system;

void EventHandler::pushEvent(EventVariant&& event)
{
	eventsQueue.push(event);
}

void EventHandler::clearEvents() noexcept
{
	
}

void EventHandler::pollEvents()
{
	while (!eventsQueue.empty())
	{
		EventVariant& event = eventsQueue.front();

		if (std::holds_alternative<InputEvent>(event))
		{
			std::cout << "input_registred\n";
			switch (std::get<InputEvent>(event).sfEvent.type)
			{
			case sf::Event::MouseButtonPressed:
				std::cout << "buttonPresed\n";
				break;

			case sf::Event::KeyPressed:
				std::cout << "key_pressed\n";
				break;

			case sf::Event::MouseWheelMoved:
				std::cout << "whell_moved\n";
				break;
			}
		}
		/*
		if (std::holds_alternative<MapChanged>(event))
		{

		}
		*/


		eventsQueue.pop();
	}
}

void EventHandler::updateInput(const sf::Event& event)
{
	for (auto& entry : bindings)
	{
		auto& binding = entry.second;

		if (binding.inputType == InputType::keyboard && event.type == sf::Event::KeyPressed)
		{
			binding.active = static_cast<sf::Keyboard::Scancode>(binding.code) == event.key.scancode;
			continue;	// scancode - the code of concrete key
		}

		if (binding.inputType == InputType::mouse && event.type == sf::Event::MouseButtonPressed)
		{
			binding.active = static_cast<sf::Mouse::Button>(binding.code) == event.mouseButton.button;
			continue;
		}

		binding.active = false;
	}
}


bool EventHandler::active(const KeyName keyName)
{
	const auto& found = bindings.find(keyName);
	if (found == bindings.end())
		return false;
	return found->second.active;
}
