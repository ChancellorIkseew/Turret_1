#pragma once

#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include <SFML\Graphics.hpp>
#include "game_interface/sub_window/sub_window/sub_window.h"


class TextField : public SubWindow
{
private:
	sf::Text text;
	sf::Vector2u ownerPosition;

public:
	TextField(const sf::String& value, const sf::Vector2u size, const sf::Vector2u position);
	TextField();
	~TextField() = default;

	void interact(const sf::Vector2i& mouseCoord);
	void relocate(const sf::Vector2u ownerPosition) override;

	void setText(const sf::String& value);
	int getIntValue();

	void prepareInterfaceSprites() override;
	void draw(sf::RenderWindow& window) override;

};

#endif // TEXT_FIELD_H
