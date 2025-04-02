
#include "ui_plate.h"

#include "game_interface/ui_window/sub_win_util/fonts.h"
#include "game_interface/ui_window/elements/res_ico/res_ico.h"
#include "game_interface/ui_window/elements/res_info/res_info.h"
#include "game_interface/ui_window/elements/button/building_ico.h"
#include "game_interface/ui_window/elements/button/checkbox.h"

#include "t1_system/input/input_handler.h"


UIPlate::UIPlate(const sf::Vector2i size, const sf::Vector2i position) :
	size(size), position(position) { }
UIPlate::UIPlate(const sf::Vector2i size) :
	size(size) { }

void UIPlate::init()
{
	prepareWindowBaseSprites();

	ResIco::prepareSprites();
	BuildingIco::prepareSprites();
	Checkbox::prepareSprites();
	initFonts();
}


void UIPlate::prepareWindowBaseSprites()
{
	//Base
	baseTexture.loadFromFile("images/ui_window/ui_window_base.bmp");
	base.setColor(sf::Color(255, 255, 255, 210));
	//Borders
	upperBorderTexture.loadFromFile("images/ui_window/ui_window_upper_border.bmp");
	lowerBorderTexture.loadFromFile("images/ui_window/ui_window_lower_border.bmp");
	leftBorderTexture.loadFromFile("images/ui_window/ui_window_left_border.bmp");
	rightBorderTexture.loadFromFile("images/ui_window/ui_window_right_border.bmp");
	//Corners
	constexpr sf::IntRect CORNER_RECT({ 0, 0 }, { 5, 5 });
	upperLeftCornerTexture.loadFromFile("images/ui_window/ui_window_upper_left_corner.bmp");
	upperLeftCorner.setTextureRect(CORNER_RECT);
	lowerLeftCornerTexture.loadFromFile("images/ui_window/ui_window_lower_left_corner.bmp");
	lowerLeftCorner.setTextureRect(CORNER_RECT);
	upperRightCornerTexture.loadFromFile("images/ui_window/ui_window_upper_right_corner.bmp");
	upperRightCorner.setTextureRect(CORNER_RECT);
	lowerRightCornerTexture.loadFromFile("images/ui_window/ui_window_lower_right_corner.bmp");
	lowerRightCorner.setTextureRect(CORNER_RECT);
}


void UIPlate::drawBase(sf::RenderWindow& window) const
{
	//Base
	base.setTextureRect(sf::IntRect({ 0, 0 }, {size.x - 10, size.y - 10}));
	base.setPosition(sf::Vector2f(position.x + 5, position.y + 5));
	window.draw(base);

	//Borders
	upperBorder.setTextureRect(sf::IntRect({ 0, 0 }, { size.x - 10, 5 }));
	upperBorder.setPosition(sf::Vector2f(position.x + 5, position.y));
	window.draw(upperBorder);

	lowerBorder.setTextureRect(sf::IntRect({ 0, 0 }, { size.x - 10, 5 }));
	lowerBorder.setPosition(sf::Vector2f(position.x + 5, position.y + size.y - 5));
	window.draw(lowerBorder);

	leftBorder.setTextureRect(sf::IntRect({ 0, 0 }, { 5, size.y - 10 }));
	leftBorder.setPosition(sf::Vector2f(position.x, position.y + 5));
	window.draw(leftBorder);

	rightBorder.setTextureRect(sf::IntRect({ 0, 0 }, { 5, size.y - 10 }));
	rightBorder.setPosition(sf::Vector2f(position.x + size.x - 5, position.y + 5));
	window.draw(rightBorder);

	//Corners
	upperLeftCorner.setPosition(sf::Vector2f(position));
	window.draw(upperLeftCorner);

	lowerLeftCorner.setPosition(sf::Vector2f(position.x, position.y + size.y - 5));
	window.draw(lowerLeftCorner);

	upperRightCorner.setPosition(sf::Vector2f(position.x + size.x - 5, position.y));
	window.draw(upperRightCorner);

	lowerRightCorner.setPosition(sf::Vector2f(position.x + size.x - 5, position.y + size.y - 5));
	window.draw(lowerRightCorner);
}


void UIPlate::setVisible(const bool value)
{
	isVisible = value;
}

bool UIPlate::containsCoursor() const
{
	sf::Vector2i mouse = InputHandler::getMouseCoord();
	return isVisible &&
		position.x <= mouse.x && (position.x + size.x) >= mouse.x &&
		position.y <= mouse.y && (position.y + size.y) >= mouse.y;
}
