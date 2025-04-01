
#include "input_handler.h"

#include "game_interface/ui_window/sub_win_types/text_field/text_field.h"

static inline int intCode(sf::Mouse::Button sfMB) {
	return static_cast<int>(sfMB);
}
static inline int intCode(sf::Keyboard::Key sfKey) {
	return static_cast<int>(sfKey);
}


void InputHandler::updateInput(const std::optional<sf::Event>& event)
{
	t1::InputType inputType = t1::InputType::keyboard;
	int code = -1;
	bool pressed = false;
	if (const auto keyPressed = event->getIf<sf::Event::KeyPressed>())
	{
		code = intCode(keyPressed->code);
		pressed = true;
	}
	else if (const auto keyReleased = event->getIf<sf::Event::KeyReleased>())
	{
		code = intCode(keyReleased->code);
	}
	else if (const auto btnPressed = event->getIf<sf::Event::MouseButtonPressed>())
	{
		inputType = t1::InputType::mouse;
		code = intCode(btnPressed->button);
		pressed = true;
	}
	else if (const auto btnreleased = event->getIf<sf::Event::MouseButtonReleased>())
	{
		inputType = t1::InputType::mouse;
		code = intCode(btnreleased->button);
	}

	for (auto& [bindName, binding] : bindings)
	{
		if (inputType != binding.inputType || code != binding.code)
			continue;
		binding.justTriggered = !binding.active;
		binding.active = pressed;
	}

	if (const auto mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>())
		mouseWheelScroll.store(static_cast<t1::MouseWheelScroll>(mouseWheelScrolled->delta), std::memory_order_relaxed);
	
	if (!TextField::isOneSeltcted())
		return;
	if (const auto textEntered = event->getIf<sf::Event::TextEntered>())
		symbolJustEntered.store(textEntered->unicode, std::memory_order_relaxed);
}


bool InputHandler::active(const t1::BindName bindName)
{
	const auto& found = bindings.find(bindName);
	if (found == bindings.end() || !found->second.active)
		return false;
	found->second.justTriggered = false;
	return true;
}

bool InputHandler::jactive(const t1::BindName bindName)
{
	const auto& found = bindings.find(bindName);
	if (found == bindings.end() || !found->second.justTriggered)
		return false;
	found->second.justTriggered = false;
	return true;
}




void InputHandler::updateMouseCoord(sf::RenderWindow& window)
{
	mouseCoord.store(sf::Mouse::getPosition(window), std::memory_order_relaxed);
	mouseMapCoord = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

sf::Vector2i InputHandler::getMouseCoord() {
	return mouseCoord.load(std::memory_order_relaxed);
}
sf::Vector2f InputHandler::getMouseMapCoord() {
	return mouseMapCoord.load(std::memory_order_relaxed);
}
t1::MouseWheelScroll InputHandler::getMouseWheelScroll() {
	return mouseWheelScroll.exchange(t1::MouseWheelScroll::none, std::memory_order_relaxed);
}
char32_t InputHandler::getLastSymbolEntered() {
	return symbolJustEntered.exchange(NON_USABLE_SYMBOL, std::memory_order_relaxed);
}


void InputHandler::rebind(const t1::BindName bindName, const std::optional<sf::Event>& event)
{
	int nCode = 0;
	t1::InputType inputType = t1::InputType::keyboard;
	if (const auto keyPressed = event->getIf<sf::Event::KeyPressed>())
	{
		nCode = intCode(keyPressed->code);
	}
	else if (const auto btnPressed = event->getIf<sf::Event::MouseButtonPressed>())
	{
		inputType = t1::InputType::mouse;
		nCode = intCode(btnPressed->button);
	}
	
	bindings.erase(bindName); // t1::Binding has no copy constructor.
	bindings.emplace(bindName, t1::Binding(nCode, inputType));
}
