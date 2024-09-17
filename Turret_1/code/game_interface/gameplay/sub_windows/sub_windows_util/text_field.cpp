
#include <iostream>
#include <sstream>

#include "text_field.h"

#include "../../../system/system.h"
#include "../../../system/text_enter.h"
#include "fonts.h"


TextField::TextField(int v_sizeX, int v_sizeY, int v_positionX, int v_positionY) : SubWindow('t', v_sizeX, v_sizeY, v_positionX, v_positionY)
{
	this->prepareInterfaceSprites();
	this->relocate(0, 0);
}



TextField::TextField() : SubWindow('t', 100, 23, 100, 100)
{
	this->prepareInterfaceSprites();
	this->relocate(0, 0);
}



void TextField::prepareInterfaceSprites()
{
	text.setFont(turretClassic);
	text.setCharacterSize(16);
	text.setFillColor(sf::Color(68, 52, 52));
}



void TextField::interact(sf::Vector2i& mouseCoord)
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



void TextField::relocate(int windowSizeX, int windowSizeY)
{

}



void TextField::draw(sf::RenderWindow& window)
{
	if (isSelected)
	{
		baseSprite.setColor(sf::Color(239, 228, 176));
	}

	drawSubWindowBase(window);
	text.setPosition(positionX + 5, positionY + 1);
	window.draw(text);
	baseSprite.setColor(sf::Color::White); // set_normal_color
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



TextField::~TextField()
{

}