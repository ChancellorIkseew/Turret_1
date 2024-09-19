
#include <iostream>
#include <SFML/Graphics.hpp>


#include "main_menu.h"

#include "game_interface/system/system.h"
#include "game_interface/main_window/main_window.h"

MainMenu::MainMenu() : SubWindow('s', 720, 480, 100, 100)
{
	this->prepareInterfaceSprites();
	this->relocate(0, 0);
}



void MainMenu::prepareInterfaceSprites()
{
	
	playButtonImage.loadFromFile("images/buttons/play.bmp");
	playButtonTexture.loadFromImage(playButtonImage);
	playButtonSprite.setTexture(playButtonTexture);
	playButtonSprite.setTextureRect(sf::IntRect(0, 0, 162, 48));
	
	optionsButtonImage.loadFromFile("images/buttons/setting.bmp");
	optionsButtonTexture.loadFromImage(optionsButtonImage);
	optionsButtonSprite.setTexture(optionsButtonTexture);
	optionsButtonSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
}



int MainMenu::interact(sf::Vector2i& mouseCoord, bool& isMenuOpen)
{
	while (isMenuOpen)
	{
		if (LMB_Pressed)
		{
			//std::cout << "LMB_pressed" << std::endl;

			if (playButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
			{
				Sleep(150);
				std::cout << "play_button_works" << std::endl;
				return CHOISE_FOLDER_MENU;
			}


			if (optionsButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
			{
				Sleep(150);
				std::cout << "options_button_works" << std::endl;

				return OPTIONS;
			}
		}

		Sleep(16);
	}

	return MAIN_MENU;
}



void MainMenu::relocate(int windowSizeX, int windowSizeY)
{
	positionX = (windowSizeX - sizeX) / 2;
	positionY = (windowSizeY - sizeY) / 2;
	//std::cout << " win x:" << positionX << " win y:" << positionY << '\n';

	playButtonSprite.setPosition(positionX+ 10, positionY + 10);
	optionsButtonSprite.setPosition(positionX + 10, positionY + 60);
}



void MainMenu::draw(sf::RenderWindow& window)
{
	if (isVisible)
	{
		this->drawSubWindowBase(window);
		window.draw(optionsButtonSprite);
		window.draw(playButtonSprite);
	}
}
