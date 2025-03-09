
#include "input_handler.h"

#include "game_interface/ui_window/sub_win_types/text_field/text_field.h"
#include <iostream>

static int code(sf::Mouse::Button sfMB) {
	return static_cast<int>(sfMB);
}
static int code(sf::Keyboard::Key sfKey) {
	return static_cast<int>(sfKey);
}


void InputHandler::updateInput(const std::optional<sf::Event>& event)
{
	t1::InputType inputType = t1::InputType::keyboard;
	int nCode = -1;
	bool pressed = false;
	if (const auto keyPressed = event->getIf<sf::Event::KeyPressed>())
	{
		nCode = code(keyPressed->code);
		pressed = true;
	}
	else if (const auto keyReleased = event->getIf<sf::Event::KeyReleased>())
	{
		nCode = code(keyReleased->code);
		pressed = false;
	}
	else if (const auto btnPressed = event->getIf<sf::Event::MouseButtonPressed>())
	{
		inputType = t1::InputType::mouse;
		nCode = code(btnPressed->button);
		pressed = true;
	}
	else if (const auto btnreleased = event->getIf<sf::Event::MouseButtonReleased>())
	{
		inputType = t1::InputType::mouse;
		nCode = code(btnreleased->button);
		pressed = false;
	}

	for (auto& [bindName, binding] : bindings)
	{
		if (inputType != binding.inputType || nCode != binding.code)
			continue;
		binding.justTriggered = !binding.active;
		binding.active = pressed;
	}

	if (const auto mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>())
	{
		mouseWheelScroll.store(static_cast<t1::MouseWheelScroll>(mouseWheelScrolled->delta), std::memory_order_relaxed);
	}
	
	if (!TextField::isOneSeltcted())
		return;
	if (const auto textEntered = event->getIf<sf::Event::TextEntered>())
	{
		symbolJustEntered.store(textEntered->unicode, std::memory_order_relaxed);
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


void InputHandler::rebind(const t1::BindName bindName, const std::optional<sf::Event>& event)
{
	int nCode = 0;
	t1::InputType inputType = t1::InputType::keyboard;
	if (const auto keyPressed = event->getIf<sf::Event::KeyPressed>())
	{
		nCode = code(keyPressed->code);
	}
	else if (const auto btnPressed = event->getIf<sf::Event::MouseButtonPressed>())
	{
		inputType = t1::InputType::mouse;
		nCode = code(btnPressed->button);
	}

	bindings.erase(bindName);
	bindings.emplace(bindName, t1::Binding(nCode, inputType));
}

using BindName = t1::BindName;
using Binding = t1::Binding;
using InputType = t1::InputType;

std::unordered_map<t1::BindName, t1::Binding> InputHandler::bindings
{
	{BindName::LMB, Binding(code(sf::Mouse::Button::Left), InputType::mouse)},
	{BindName::RMB, Binding(code(sf::Mouse::Button::Right), InputType::mouse)},
	{BindName::MidMB, Binding(code(sf::Mouse::Button::Middle), InputType::mouse)},

	{BindName::Build, Binding(code(sf::Mouse::Button::Left), InputType::mouse)},
	{BindName::Rotate_building, Binding(code(sf::Keyboard::Key::R), InputType::keyboard)},

	{BindName::Control_unit, Binding(code(sf::Keyboard::Key::V), InputType::keyboard)},
	{BindName::Shoot, Binding(code(sf::Mouse::Button::Left), InputType::mouse)},

	{BindName::Move_up, Binding(code(sf::Keyboard::Key::W), InputType::keyboard)},
	{BindName::Move_left, Binding(code(sf::Keyboard::Key::A), InputType::keyboard)},
	{BindName::Move_down, Binding(code(sf::Keyboard::Key::S), InputType::keyboard)},
	{BindName::Move_right, Binding(code(sf::Keyboard::Key::D), InputType::keyboard)},

	{BindName::Pause, Binding(code(sf::Keyboard::Key::Space), InputType::keyboard)},
	{BindName::Cancel, Binding(code(sf::Keyboard::Key::Escape), InputType::keyboard)},
	{BindName::Escape, Binding(code(sf::Keyboard::Key::Escape), InputType::keyboard)},
	{BindName::Console_cheat, Binding(code(sf::Keyboard::Key::RAlt), InputType::keyboard)}
};
