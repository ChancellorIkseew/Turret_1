
#include <iostream>
#include <SFML/Graphics.hpp>


#include "main_menu.h"

#include "game_interface/system/system.h"
#include "game_interface/system/sleep.h"
#include "game_interface/main_window/main_window.h"

MainMenu::MainMenu() : SubWindow('s', 720, 480, 100, 100)
{
	this->prepareInterfaceSprites();
	this->relocate(0, 0);
}



void MainMenu::prepareInterfaceSprites()
{
	play = Button("play.bmp", sf::Vector2i(162, 48), sf::Vector2i(10, 10));
	settings = Button("settings.bmp", sf::Vector2i(48, 48), sf::Vector2i(10, 60));
}



int MainMenu::interact(sf::Vector2i& mouseCoord, bool& isMenuOpen)
{
	while (isMenuOpen)
	{
		if (play.press(mouseCoord))
			return CHOISE_FOLDER_MENU;

		if (settings.press(mouseCoord))
			return OPTIONS;

		t1::system::sleep(16);
	}

	return MAIN_MENU;
}



void MainMenu::relocate(int windowSizeX, int windowSizeY)
{
	positionX = (windowSizeX - sizeX) / 2;
	positionY = (windowSizeY - sizeY) / 2;

	play.relocate(sf::Vector2i(positionX, positionY));
	settings.relocate(sf::Vector2i(positionX, positionY));
}



void MainMenu::draw(sf::RenderWindow& window)
{
	if (isVisible)
	{
		this->drawSubWindowBase(window);
		play.draw(window);
		settings.draw(window);
	}
}
