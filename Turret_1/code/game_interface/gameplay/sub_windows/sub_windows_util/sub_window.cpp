
#include <SFML/Graphics.hpp>

#include "sub_window.h"

#include "fonts.h"
#include "res_info.h"


SubWindow::SubWindow(char type, int sizeX, int sizeY, int positionX, int positionY)
{
	this->windowType = type;

	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->positionX = positionX;
	this->positionY = positionY;

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



void SubWindow::prepareInterfaceSprites()
{

}



void SubWindow::drawSubWindowBase(sf::RenderWindow& window)
{
	//Base
	baseSprite.setTextureRect(sf::IntRect(0, 0, sizeX-10, sizeY-10));
	baseSprite.setPosition(positionX+5, positionY + 5);
	window.draw(baseSprite);

	//Borders

	//Upper_border
	upperBorderSprite.setTextureRect(sf::IntRect(0, 0, sizeX-10, 5));
	upperBorderSprite.setPosition(positionX + 5, positionY);
	window.draw(upperBorderSprite);
	
	//Lower_border
	lowerBorderSprite.setTextureRect(sf::IntRect(0, 0, sizeX - 10, 5));
	lowerBorderSprite.setPosition(positionX + 5, positionY + sizeY - 5);
	window.draw(lowerBorderSprite);
	
	//Left_border
	leftBorderSprite.setTextureRect(sf::IntRect(0, 0, 5, sizeY -10));
	leftBorderSprite.setPosition(positionX, positionY + 5);
	window.draw(leftBorderSprite);

	//Right_border
	rightBorderSprite.setTextureRect(sf::IntRect(0, 0, 5, sizeY - 10));
	rightBorderSprite.setPosition(positionX + sizeX - 5, positionY + 5);
	window.draw(rightBorderSprite);
	
	//Corners

	//Upper_left_corner
	upperLeftCornerSprite.setPosition(positionX, positionY);
	window.draw(upperLeftCornerSprite);

	lowerLeftCornerSprite.setPosition(positionX, positionY + sizeY - 5);
	window.draw(lowerLeftCornerSprite);

	upperRightCornerSprite.setPosition(positionX + sizeX - 5, positionY);
	window.draw(upperRightCornerSprite);

	lowerRightCornerSprite.setPosition(positionX + sizeX - 5, positionY + sizeY - 5);
	window.draw(lowerRightCornerSprite);

	return;
}


void SubWindow::draw(sf::RenderWindow& window)
{
	this->drawSubWindowBase(window);
}


void SubWindow::relocate(int windowSizeX, int windowSizeY)
{

}



void SubWindow::setVisible(bool trueOrFalse)
{
	isVisible = trueOrFalse;
}



void SubWindow::setPosition(int v_positionX, int v_positionY)
{
	positionX = v_positionX;
	positionY = v_positionY;
}



bool SubWindow::containsCoursor(sf::Vector2i& mouseCoord)
{
	if (isVisible && 
		positionX <= mouseCoord.x && (positionX + sizeX) >= mouseCoord.x && 
		positionY <= mouseCoord.y && (positionY + sizeY) >= mouseCoord.y)
	{
		return true;
	}

	return false;
}
