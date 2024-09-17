#pragma once

#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include <iostream>
#include <string>
#include <SFML\Graphics.hpp>

#include "sub_window.h"


class TextField : public SubWindow
{
private:

	sf::Text text;

public:

	TextField(int v_sizeX, int v_sizeY, int v_positionX, int v_positionY);

	TextField();

	void prepareInterfaceSprites() override;

	void interact(sf::Vector2i& mouseCoord);

	void relocate(int windowSizeX, int windowSizeY) override;

	void draw(sf::RenderWindow& window) override;

	void setText(sf::String v_text);

	int getIntValue();

	~TextField();

};


#endif // TEXT_FIELD_H
