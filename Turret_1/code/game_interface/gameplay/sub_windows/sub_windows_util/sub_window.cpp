
#include <SFML/Graphics.hpp>

#include "sub_window.h"

#include "fonts.h"
#include "res_info.h"


SubWindow::SubWindow(char type, const sf::Vector2u size, const sf::Vector2u position)
{
	this->windowType = type;
	this->size = size;
	this->position = position;

	isSelected = false;
	isVisible = true;
}


void SubWindow::init()
{
	prepareWindowBaseSprites();

	ResInfo::prepareSprites();
	initFonts();
}


void SubWindow::prepareWindowBaseSprites()
{
	//Base
	baseImage.loadFromFile("images/sub_window/sub_window_base.bmp");
	//Borders
	upperBorderImage.loadFromFile("images/sub_window/sub_window_upper_border.bmp");
	lowerBorderImage.loadFromFile("images/sub_window/sub_window_lower_border.bmp");
	leftBorderImage.loadFromFile("images/sub_window/sub_window_left_border.bmp");
	rightBorderImage.loadFromFile("images/sub_window/sub_window_right_border.bmp");
	//Corners
	upperLeftCornerImage.loadFromFile("images/sub_window/sub_window_upper_left_corner.bmp");
	lowerLeftCornerImage.loadFromFile("images/sub_window/sub_window_lower_left_corner.bmp");
	upperRightCornerImage.loadFromFile("images/sub_window/sub_window_upper_right_corner.bmp");
	lowerRightCornerImage.loadFromFile("images/sub_window/sub_window_lower_right_corner.bmp");

	//Base
	baseTexture.loadFromImage(baseImage);
	baseSprite.setTexture(baseTexture);
	baseSprite.setColor(sf::Color(255, 255, 255, 210));
	//Borders
	upperBorderTexture.loadFromImage(upperBorderImage);
	upperBorderSprite.setTexture(upperBorderTexture);

	lowerBorderTexture.loadFromImage(lowerBorderImage);
	lowerBorderSprite.setTexture(lowerBorderTexture);

	leftBorderTexture.loadFromImage(leftBorderImage);
	leftBorderSprite.setTexture(leftBorderTexture);

	rightBorderTexture.loadFromImage(rightBorderImage);
	rightBorderSprite.setTexture(rightBorderTexture);
	//Corners
	upperLeftCornerTexture.loadFromImage(upperLeftCornerImage);
	upperLeftCornerSprite.setTexture(upperLeftCornerTexture);
	upperLeftCornerSprite.setTextureRect(sf::IntRect(0, 0, 5, 5));

	lowerLeftCornerTexture.loadFromImage(lowerLeftCornerImage);
	lowerLeftCornerSprite.setTexture(lowerLeftCornerTexture);
	lowerLeftCornerSprite.setTextureRect(sf::IntRect(0, 0, 5, 5));

	upperRightCornerTexture.loadFromImage(upperRightCornerImage);
	upperRightCornerSprite.setTexture(upperRightCornerTexture);
	upperRightCornerSprite.setTextureRect(sf::IntRect(0, 0, 5, 5));

	lowerRightCornerTexture.loadFromImage(lowerRightCornerImage);
	lowerRightCornerSprite.setTexture(lowerRightCornerTexture);
	lowerRightCornerSprite.setTextureRect(sf::IntRect(0, 0, 5, 5));
}


void SubWindow::drawSubWindowBase(sf::RenderWindow& window)
{
	//Base
	baseSprite.setTextureRect(sf::IntRect(0, 0, size.x - 10, size.y - 10));
	baseSprite.setPosition(position.x + 5, position.y + 5);
	window.draw(baseSprite);

	//Borders

	//Upper_border
	upperBorderSprite.setTextureRect(sf::IntRect(0, 0, size.x - 10, 5));
	upperBorderSprite.setPosition(position.x + 5, position.y);
	window.draw(upperBorderSprite);
	
	//Lower_border
	lowerBorderSprite.setTextureRect(sf::IntRect(0, 0, size.x - 10, 5));
	lowerBorderSprite.setPosition(position.x + 5, position.y + size.y - 5);
	window.draw(lowerBorderSprite);
	
	//Left_border
	leftBorderSprite.setTextureRect(sf::IntRect(0, 0, 5, size.y -10));
	leftBorderSprite.setPosition(position.x, position.y + 5);
	window.draw(leftBorderSprite);

	//Right_border
	rightBorderSprite.setTextureRect(sf::IntRect(0, 0, 5, size.y - 10));
	rightBorderSprite.setPosition(position.x + size.x - 5, position.y + 5);
	window.draw(rightBorderSprite);
	
	//Corners

	//Upper_left_corner
	upperLeftCornerSprite.setPosition(position.x, position.y);
	window.draw(upperLeftCornerSprite);

	lowerLeftCornerSprite.setPosition(position.x, position.y + size.y - 5);
	window.draw(lowerLeftCornerSprite);

	upperRightCornerSprite.setPosition(position.x + size.x - 5, position.y);
	window.draw(upperRightCornerSprite);

	lowerRightCornerSprite.setPosition(position.x + size.x - 5, position.y + size.y - 5);
	window.draw(lowerRightCornerSprite);

	return;
}


void SubWindow::draw(sf::RenderWindow& window)
{
	this->drawSubWindowBase(window);
}


void SubWindow::relocateCentral(const sf::Vector2u windowSize)
{
	position = sf::Vector2u((windowSize.x - size.x) / 2, (windowSize.y - size.y) / 2);
}

void SubWindow::relocate(const sf::Vector2u windowSize) { }


void SubWindow::setVisible(bool value)
{
	isVisible = value;
}



void SubWindow::setPosition(const sf::Vector2u position)
{
	this->position = position;
}



bool SubWindow::containsCoursor(const sf::Vector2i& mouseCoord) const
{
	if (isVisible && 
		position.x <= mouseCoord.x && (position.x + size.x) >= mouseCoord.x && 
		position.y <= mouseCoord.y && (position.y + size.y) >= mouseCoord.y)
	{
		return true;
	}

	return false;
}
