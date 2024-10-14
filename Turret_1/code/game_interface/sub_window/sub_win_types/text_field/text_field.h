#pragma once

#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include <SFML\Graphics.hpp>
#include "game_interface/sub_window/sub_window/sub_window.h"


class TextField : public SubWindow
{
private:

	sf::Text text;

public:

	TextField(const sf::Vector2u size, const sf::Vector2u position);
	TextField();
	~TextField() = default;

	void interact(const sf::Vector2i& mouseCoord);
	void relocate(const sf::Vector2u windowSizeY) override;

	void setText(sf::String v_text);
	int getIntValue();

	void prepareInterfaceSprites() override;
	void draw(sf::RenderWindow& window) override;

};

#endif // TEXT_FIELD_H
