
#include <sstream>
#include <limits>

#include "text_field.h"

#include "t1_system/input/input_handler.h"
#include "t1_system/sleep.h"
#include "t1_system/t1_mutex.h"


TextField::TextField(const sf::String& value, const int sizeX, const sf::Vector2i  position) : UIPlate(sf::Vector2i(sizeX, 23), position)
{
	this->prepareInterfaceSprites();
	text.setString(value);
	maxLenght = (sizeX - 10) / 8;
}

TextField::TextField() : UIPlate(sf::Vector2i(100, 23), sf::Vector2i(0, 0))
{
	this->prepareInterfaceSprites();
}


void TextField::prepareInterfaceSprites()
{
	text.setCharacterSize(16);
	text.setFillColor(sf::Color(68, 52, 52));
}


void TextField::interact()
{
	if (!isSelected && text.getString().getSize() < 1)
		text.setString("0");
	if (!containsCoursor() || !InputHandler::jactive(t1::BindName::LMB))
		return;
	isSelected = true;
	isOneSelected = true;
	while (!InputHandler::jactive(t1::BindName::LMB))
	{
		const char32_t sym = InputHandler::getLastSymbolEntered();
		t1::system::sleep(50);

		if ((sym >= '0' && sym <= '9' || sym == '.') && text.getString().getSize() < maxLenght)
		{
			text.setString(text.getString() + sym);
		}
		else if (sym == 8) // backspace
		{
			std::string str = text.getString();
			std::string new_str = str.substr(0, str.length() - 1);
			text.setString(new_str);
		}
	}
	isSelected = false;
	isOneSelected = false;
}


void TextField::relocateWithOwner(const sf::Vector2i ownerPosition)
{
	position -= this->ownerPosition;
	this->ownerPosition = ownerPosition;
	position += this->ownerPosition;
	text.setPosition(sf::Vector2f(position.x + 5, position.y + 1));
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


uint32_t TextField::getValueUint32() // need to chek it in other compilers and OS
{
	if (text.getString().isEmpty())
		return 0;
	const std::string str = text.getString();
	uint32_t value = std::numeric_limits<uint32_t>::max();
	try { value = std::stoul(str); }
	catch (const std::out_of_range& exception) {}
	return value;
}

float TextField::getValueFloat()
{
	if (text.getString().isEmpty())
		return 0.0f;
	const std::string str = text.getString();
	float value = 1.0f;
	try { value = std::stof(str); }
	catch (const std::out_of_range& exception) {}
	return value;
}
