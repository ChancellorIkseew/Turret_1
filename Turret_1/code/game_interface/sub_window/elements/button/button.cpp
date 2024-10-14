
#include "button.h"
#include "game_interface/system/sleep.h"
#include "game_interface/system/system.h"


Button::Button(const std::string& imageFile, const sf::Vector2i size, const sf::Vector2i position)
{
	this->size = size;
	this->position = position;

	image.loadFromFile("images/buttons/" + imageFile);
	image.createMaskFromColor(sf::Color(0, 255, 0));
	texture.loadFromImage(image);
	button.setTexture(texture);
	button.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
	button.setOrigin(0.0f, 0.0f);
}

Button& Button::operator=(const Button& other)
{
	size = other.size;
	position = other.position;
	image = other.image;
	name = other.name;

	texture.loadFromImage(image);
	button.setTexture(texture);
	button.setTextureRect(sf::IntRect(0, 0, size.x, size.y));

	isVisible = true;
	isSelected = false;
	isPressed = false;

	return *this;
}


bool Button::select(const sf::Vector2i& mouseCoord)
{
	if (button.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
	{
		isSelected = true;
		return true;
	}
	isSelected = false;
	return false;
}

bool Button::press(const sf::Vector2i& mouseCoord)
{
	if (!isVisible)
		return false;

	if (select(mouseCoord))
	{
		if (LMB_Pressed)
		{
			isPressed = true;
			t1::system::sleep(150);
			isPressed = false;
			return true;
		}
	}
	return false;
}

void Button::setVisible(const bool visible)
{
	isVisible = visible;
}



void Button::relocate(const sf::Vector2u subWinPosition)
{
	button.setPosition(float(subWinPosition.x + position.x), float(subWinPosition.y + position.y));
}

void Button::draw(sf::RenderWindow& window)
{
	if (!isVisible)
		return;
	
	if (isSelected && !isPressed)
	{
		button.setTextureRect(sf::IntRect(0, size.y, size.x, size.y));
	}

	if (isPressed)
	{
		button.setTextureRect(sf::IntRect(0, size.y * 2, size.x, size.y));
	}

	if (!isSelected && !isPressed)
	{
		button.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
	}
	
	window.draw(button);
}
