
#include "input_handler.h"
#include <iostream>


void InputHandler::updateInput(const sf::Event& event)
{
	for (auto& entry : bindings)
	{
		auto& binding = entry.second;

		if (binding.inputType == t1::InputType::keyboard && event.type == sf::Event::KeyPressed)
		{
			binding.active = static_cast<sf::Keyboard::Scancode>(binding.code) == event.key.scancode;
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

	}
}

///@brief cheek long press
bool InputHandler::active(const t1::KeyName keyName)
{
	const auto& found = bindings.find(keyName);
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
bool InputHandler::jactive(const t1::KeyName keyName)
{
	const auto& found = bindings.find(keyName);
	if (found == bindings.end())
		return false;
	if (found->second.active && found->second.justTriggered)
	{
		found->second.justTriggered = false;
		return true;
	}
	return false;
}


void InputHandler::rebind(const t1::KeyName keyName, const sf::Event& event)
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

	bindings.erase(keyName);
	bindings.emplace(keyName, t1::Binding(code, inputType));
}

using KeyName = t1::KeyName;
using Binding = t1::Binding;
using InputType = t1::InputType;

std::unordered_map<t1::KeyName, t1::Binding> InputHandler::bindings
{
	{KeyName::LMB, Binding(sf::Mouse::Left, InputType::mouse)},
	{KeyName::RMB, Binding(sf::Mouse::Right, InputType::mouse)},
	{KeyName::MidMB, Binding(sf::Mouse::Middle, InputType::mouse)},

	{KeyName::Build, Binding(sf::Mouse::Left, InputType::mouse)},
	{KeyName::Rotate_building, Binding(sf::Mouse::Right, InputType::mouse)},

	{KeyName::Move_up, Binding(sf::Keyboard::W, InputType::keyboard)},
	{KeyName::Move_left, Binding(sf::Keyboard::A, InputType::keyboard)},
	{KeyName::Move_down, Binding(sf::Keyboard::S, InputType::keyboard)},
	{KeyName::Move_right, Binding(sf::Keyboard::D, InputType::keyboard)},

	{KeyName::Console_cheat, Binding(sf::Keyboard::RAlt, InputType::keyboard)}
};
