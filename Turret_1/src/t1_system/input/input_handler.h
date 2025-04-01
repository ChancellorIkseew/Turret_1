#pragma once
#ifndef T1_SYSTEM_INPUT_HANDLER_H
#define T1_SYSTEM_INPUT_HANDLER_H

#include <unordered_map>
#include "t1_input.h"


class InputHandler
{
private:
	static std::unordered_map<t1::BindName, t1::Binding> bindings;
	static inline constexpr char32_t NON_USABLE_SYMBOL = static_cast<char32_t>(0);
	static inline std::atomic<char32_t> symbolJustEntered = NON_USABLE_SYMBOL;
	static inline std::atomic<sf::Vector2i> mouseCoord = sf::Vector2i(0, 0);
	static inline std::atomic<sf::Vector2f> mouseMapCoord = sf::Vector2f(0.0f, 0.0f);
	static inline std::atomic<t1::MouseWheelScroll> mouseWheelScroll = t1::MouseWheelScroll::none;

public:
	InputHandler() = default;
	~InputHandler() = default;

	static void updateInput(const std::optional<sf::Event>& event);
	///@brief Check any press/click.
	static bool active(const t1::BindName bindName);
	///@brief Check only short press/click.
	static bool jactive(const t1::BindName bindName);
	///@brief Last symbol entered in any text field.
	static char32_t getLastSymbolEntered();

	static void updateMouseCoord(sf::RenderWindow& window);
	///@brief Coordinate in SFML window.
	static sf::Vector2i getMouseCoord();
	///@brief Pixel coordinate on map.
	static sf::Vector2f getMouseMapCoord();
	///@brief (none/up/down)
	static t1::MouseWheelScroll getMouseWheelScroll();

	static void rebind(const t1::BindName keyName, const std::optional<sf::Event>& event);
};

#endif // T1_SYSTEM_INPUT_HANDLER_H
