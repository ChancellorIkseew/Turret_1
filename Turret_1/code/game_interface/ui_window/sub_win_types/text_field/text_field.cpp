
#include <iostream>
#include <sstream>

#include "text_field.h"

#include "t1_system/input/input_handler.h"
#include "t1_system/sleep.h"
#include "t1_system/t1_mutex.h"
#include "game_interface/ui_window/sub_win_util/fonts.h"
#include "game_interface/main_window/main_window.h"


TextField::TextField(const sf::String& value, const uint32_t sizeX, const sf::Vector2u  position) : UIPlate(sf::Vector2u(sizeX, 23), position)
{
	this->prepareInterfaceSprites();
	text.setString(value);
	maxLenght = (sizeX - 10) / 8;
}

TextField::TextField() : UIPlate(sf::Vector2u(100, 23), sf::Vector2u(0, 0))
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
	if (containsCoursor(mouseCoord) && InputHandler::jactive(t1::KeyName::LMB))
	{
		isSelected = true;
		isOneSelected = true;
		t1::system::sleep(150);

		while (true)
		{
			char32_t sym = InputHandler::getTextEntered();
			t1::system::sleep(50);

			if (sym > 47 && sym < 58 && text.getString().getSize() < maxLenght)
			{
				text.setString(text.getString() + sym);
			}
			else if (sym == 8)
			{
				std::string str = text.getString();
				std::string new_str = str.substr(0, str.length() - 1);
				text.setString(new_str);
			}

			if (InputHandler::jactive(t1::KeyName::LMB))
			{
				isSelected = false;
				isOneSelected = false;
				return;
			}
		}
	}

	if (!isSelected && text.getString().getSize() < 1)
		text.setString("0");
}


void TextField::relocateWithOwner(const sf::Vector2u ownerPosition)
{
	position -= this->ownerPosition;
	this->ownerPosition = ownerPosition;
	position += this->ownerPosition;
	text.setPosition(position.x + 5, position.y + 1);
}


void TextField::draw(sf::RenderWindow& window)
{
	if (isSelected)
		base.setColor(sf::Color(239, 228, 176));
	drawBase(window);
	window.draw(text);
	base.setColor(sf::Color(255, 255, 255, 210)); // set_normal_color
}


void TextField::setText(const sf::String& value)
{
	text.setString(value);
}


int TextField::getIntValue()
{
	if (text.getString().getSize() < 1)
		return 0;
	std::string str = text.getString();
	return std::stoi(str);
}
