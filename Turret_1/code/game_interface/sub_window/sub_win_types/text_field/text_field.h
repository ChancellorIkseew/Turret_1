#pragma once

#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include <SFML\Graphics.hpp>
#include "game_interface/sub_window/sub_window/sub_window.h"


class TextField : public SubWindow
{
private:
	int8_t maxLenght;
	sf::Text text;
	sf::Vector2u ownerPosition;
	static inline bool isOneSelected = false;

public:
	TextField(const sf::String& value, const uint32_t sizeX, const sf::Vector2u position);
	TextField();
	~TextField() = default;

	void interact(const sf::Vector2i& mouseCoord);
	void relocate(const sf::Vector2u ownerPosition) override final;
	static bool isOneSeltcted() { return isOneSelected; }

	void setText(const sf::String& value);
	int getIntValue();

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};

#endif // TEXT_FIELD_H
