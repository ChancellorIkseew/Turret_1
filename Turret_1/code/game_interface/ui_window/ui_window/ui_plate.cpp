
#include <SFML/Graphics.hpp>

#include "ui_plate.h"

#include "game_interface/ui_window/sub_win_util/fonts.h"
#include "game_interface/ui_window/elements/res_ico/res_ico.h"
#include "game_interface/ui_window/elements/res_info/res_info.h"
#include "game_interface/ui_window/elements/button/building_ico.h"

#include "t1_system/input/input_handler.h"


UIPlate::UIPlate(const sf::Vector2u size, const sf::Vector2u position)
{
	this->size = size;
	this->position = position;

	isSelected = false;
	isVisible = true;
}


void UIPlate::init()
{
	prepareWindowBaseSprites();

	ResIco::prepareSprites();
	BuildingIco::prepareSprites();
	initFonts();
}


void UIPlate::prepareWindowBaseSprites()
{
	//Base
	baseTexture.loadFromFile("images/ui_window/ui_window_base.bmp");
	base.setTexture(baseTexture);
	base.setColor(sf::Color(255, 255, 255, 210));
	//Borders
	upperBorderTexture.loadFromFile("images/ui_window/ui_window_upper_border.bmp");
	upperBorder.setTexture(upperBorderTexture);

	lowerBorderTexture.loadFromFile("images/ui_window/ui_window_lower_border.bmp");
	lowerBorder.setTexture(lowerBorderTexture);

	leftBorderTexture.loadFromFile("images/ui_window/ui_window_left_border.bmp");
	leftBorder.setTexture(leftBorderTexture);

	rightBorderTexture.loadFromFile("images/ui_window/ui_window_right_border.bmp");
	rightBorder.setTexture(rightBorderTexture);
	//Corners
	upperLeftCornerTexture.loadFromFile("images/ui_window/ui_window_upper_left_corner.bmp");
	upperLeftCorner = sf::Sprite(upperLeftCornerTexture, sf::IntRect(0, 0, 5, 5));

	lowerLeftCornerTexture.loadFromFile("images/ui_window/ui_window_lower_left_corner.bmp");
	lowerLeftCorner = sf::Sprite(lowerLeftCornerTexture, sf::IntRect(0, 0, 5, 5));

	upperRightCornerTexture.loadFromFile("images/ui_window/ui_window_upper_right_corner.bmp");
	upperRightCorner = sf::Sprite(upperRightCornerTexture, sf::IntRect(0, 0, 5, 5));

	lowerRightCornerTexture.loadFromFile("images/ui_window/ui_window_lower_right_corner.bmp");
	lowerRightCorner = sf::Sprite(lowerRightCornerTexture, sf::IntRect(0, 0, 5, 5));
}


void UIPlate::drawBase(sf::RenderWindow& window) const
{
	//Base
	base.setTextureRect(sf::IntRect(0, 0, size.x - 10, size.y - 10));
	base.setPosition(position.x + 5, position.y + 5);
	window.draw(base);

	//Borders
	upperBorder.setTextureRect(sf::IntRect(0, 0, size.x - 10, 5));
	upperBorder.setPosition(position.x + 5, position.y);
	window.draw(upperBorder);

	lowerBorder.setTextureRect(sf::IntRect(0, 0, size.x - 10, 5));
	lowerBorder.setPosition(position.x + 5, position.y + size.y - 5);
	window.draw(lowerBorder);

	leftBorder.setTextureRect(sf::IntRect(0, 0, 5, size.y - 10));
	leftBorder.setPosition(position.x, position.y + 5);
	window.draw(leftBorder);

	rightBorder.setTextureRect(sf::IntRect(0, 0, 5, size.y - 10));
	rightBorder.setPosition(position.x + size.x - 5, position.y + 5);
	window.draw(rightBorder);

	//Corners
	upperLeftCorner.setPosition(position.x, position.y);
	window.draw(upperLeftCorner);

	lowerLeftCorner.setPosition(position.x, position.y + size.y - 5);
	window.draw(lowerLeftCorner);

	upperRightCorner.setPosition(position.x + size.x - 5, position.y);
	window.draw(upperRightCorner);

	lowerRightCorner.setPosition(position.x + size.x - 5, position.y + size.y - 5);
	window.draw(lowerRightCorner);

	return;
}


void UIPlate::setVisible(const bool value)
{
	isVisible = value;
}

bool UIPlate::containsCoursor() const
{
	sf::Vector2i mouseCoord = InputHandler::getMouseCoord();
	return isVisible &&
		position.x <= mouseCoord.x && (position.x + size.x) >= mouseCoord.x &&
		position.y <= mouseCoord.y && (position.y + size.y) >= mouseCoord.y;
}
