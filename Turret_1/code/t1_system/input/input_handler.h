#pragma once
#ifndef T1_SYSTEM_INPUT_HANDLER_H
#define T1_SYSTEM_INPUT_HANDLER_H

#include <unordered_map>
#include "t1_input.h"


class InputHandler
{
private:
	static std::unordered_map<t1::KeyName, t1::Binding> bindings;
	static inline constexpr char32_t NON_USABLE_SYMBOL = static_cast<char32_t>(0);
	static inline std::atomic<char32_t> symbolJustEntered = NON_USABLE_SYMBOL;
	static inline std::atomic<sf::Vector2i> mouseCoord = sf::Vector2i(0, 0);
	static inline sf::Vector2f mouseMapCoord;

public:
	InputHandler() = default;
	~InputHandler() = default;

	static void updateInput(const sf::Event& event);

	static bool active(const t1::KeyName keyName);
	static bool jactive(const t1::KeyName keyName);
	static char32_t getLastSymbolEntered();

	static void updateMouseCoord(sf::RenderWindow& window);
	static sf::Vector2i getMouseCoord();
	static sf::Vector2f getMouseMapCoord();

	static void rebind(const t1::KeyName keyName, const sf::Event& event);
};

#endif // T1_SYSTEM_INPUT_HANDLER_H
