
#include <iostream>
#include <sstream>

#include "text_field.h"

#include "game_interface/system/system.h"
#include "game_interface/system/text_enter.h"
#include "game_interface/sub_window/sub_win_util/fonts.h"


TextField::TextField(const sf::Vector2u size, const sf::Vector2u  position) : SubWindow('t', size, position)
{
	this->prepareInterfaceSprites();
}

TextField::TextField() : SubWindow('t', sf::Vector2u(100, 23), sf::Vector2u(100, 100))
{
	this->prepareInterfaceSprites();
}


void TextField::prepareInterfaceSprites()
{
	text.setFont(turretClassic);
	text.setCharacterSize(16);
	text.setFillColor(sf::Color(68, 52, 52));
}


void TextField::interact(const sf::Vector2i& mouseCoord)
{
	if (containsCoursor(mouseCoord) && LMB_Pressed)
	{
		isSelected = true;
		Sleep(150);

		while (true)
		{
			enterText(text);
			
			if (containsCoursor(mouseCoord) && LMB_Pressed)
			{
				isSelected = false;
				Sleep(150);
				return;
			}

			Sleep(16);
		}
	}
}


void TextField::relocate(const sf::Vector2u windowSize)
{

}


void TextField::draw(sf::RenderWindow& window)
{
	if (isSelected)
	{
		baseSprite.setColor(sf::Color(239, 228, 176));
	}

	drawSubWindowBase(window);
	text.setPosition(position.x + 5, position.y + 1);
	window.draw(text);
	baseSprite.setColor(sf::Color(255, 255, 255, 210)); // set_normal_color
}


void TextField::setText(sf::String v_text)
{
	text.setString(v_text);
}


int TextField::getIntValue()
{
	std::string str = text.getString();
	return std::stoi(str);
}
