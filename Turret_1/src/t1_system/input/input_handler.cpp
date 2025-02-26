
#include "input_handler.h"

#include "game_interface/ui_window/sub_win_types/text_field/text_field.h"


void InputHandler::updateInput(const sf::Event& event)
{
	for (auto& entry : bindings)
	{
		auto& binding = entry.second;

		if (binding.inputType == t1::InputType::keyboard &&
			static_cast<sf::Keyboard::Scancode>(binding.code) == event.key.scancode)
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (!binding.active)
					binding.justTriggered = true;
				binding.active = true;
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				binding.active = false;
				binding.justTriggered = false;
			}
			continue;	// scancode - the code of concrete key
		}

		if (binding.inputType == t1::InputType::mouse &&
			static_cast<sf::Mouse::Button>(binding.code) == event.mouseButton.button)
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (!binding.active)
					binding.justTriggered = true;
				binding.active = true;
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				binding.active = false;
				binding.justTriggered = false;
			}
			continue;
		}
	}

	if (event.type == sf::Event::MouseWheelScrolled)
	{
		mouseWheelScroll.store(static_cast<t1::MouseWheelScroll>(event.mouseWheelScroll.delta), std::memory_order_relaxed);
	}

	if (event.type == sf::Event::TextEntered && TextField::isOneSeltcted())
	{
		symbolJustEntered.store(event.text.unicode, std::memory_order_relaxed);
	}
}

///@brief cheek long press
bool InputHandler::active(const t1::BindName bindName)
{
	const auto& found = bindings.find(bindName);
	if (found == bindings.end())
		return false;
	if (found->second.active)
	{
		found->second.justTriggered = false;
		return true;
	}
	return false;
}

///@brief cheek short press
bool InputHandler::jactive(const t1::BindName bindName)
{
	const auto& found = bindings.find(bindName);
	if (found == bindings.end())
		return false;
	if (found->second.active && found->second.justTriggered)
	{
		found->second.justTriggered = false;
		return true;
	}
	return false;
}

char32_t InputHandler::getLastSymbolEntered()
{
	return symbolJustEntered.exchange(NON_USABLE_SYMBOL, std::memory_order_relaxed);
}


void InputHandler::updateMouseCoord(sf::RenderWindow& window)
{
	mouseCoord.store(sf::Mouse::getPosition(window), std::memory_order_relaxed);
	mouseMapCoord = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

///@brief coordinate in SFML window
sf::Vector2i InputHandler::getMouseCoord()
{
	return mouseCoord.load(std::memory_order_relaxed);
}

///@brief coordinate on map
sf::Vector2f InputHandler::getMouseMapCoord()
{
	return mouseMapCoord.load(std::memory_order_relaxed);
}

t1::MouseWheelScroll InputHandler::getMouseWheelScroll()
{
	return mouseWheelScroll.exchange(t1::MouseWheelScroll::none, std::memory_order_relaxed);
}


void InputHandler::rebind(const t1::BindName bindName, const sf::Event& event)
{
	int code = 0;
	t1::InputType inputType = t1::InputType::keyboard;
	if (event.type == sf::Event::KeyPressed)
	{
		code = static_cast<int>(event.key.scancode);
	}
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		inputType = t1::InputType::mouse;
		code = static_cast<int>(event.mouseButton.button);
	}

	bindings.erase(bindName);
	bindings.emplace(bindName, t1::Binding(code, inputType));
}

using BindName = t1::BindName;
using Binding = t1::Binding;
using InputType = t1::InputType;

std::unordered_map<t1::BindName, t1::Binding> InputHandler::bindings
{
	{BindName::LMB, Binding(sf::Mouse::Left, InputType::mouse)},
	{BindName::RMB, Binding(sf::Mouse::Right, InputType::mouse)},
	{BindName::MidMB, Binding(sf::Mouse::Middle, InputType::mouse)},

	{BindName::Build, Binding(sf::Mouse::Left, InputType::mouse)},
	{BindName::Rotate_building, Binding(sf::Mouse::Right, InputType::mouse)},

	{BindName::Move_up, Binding(sf::Keyboard::W, InputType::keyboard)},
	{BindName::Move_left, Binding(sf::Keyboard::A, InputType::keyboard)},
	{BindName::Move_down, Binding(sf::Keyboard::S, InputType::keyboard)},
	{BindName::Move_right, Binding(sf::Keyboard::D, InputType::keyboard)},

	{BindName::Pause, Binding(sf::Keyboard::P, InputType::keyboard)},
	{BindName::Console_cheat, Binding(sf::Keyboard::RAlt, InputType::keyboard)}
};
