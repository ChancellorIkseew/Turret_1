
#include <iostream>

#include "pre_settings.h"

#include "game_interface/system/system.h"
#include "game_interface/main_window/main_window.h"

#include "world_pre_settings/general_pre_settings.h"


PreSettingsWindow::PreSettingsWindow(): SubWindow('s', 720, 480, 100, 100)
{
	isVisible = false;
	this->prepareInterfaceSprites();
	this->relocate(0, 0);
}



void PreSettingsWindow::prepareInterfaceSprites()
{
	etmButtonImage.loadFromFile("images/buttons/exit_to_menu.bmp");				//Button_exit_to_menu
	etmButtonTexture.loadFromImage(etmButtonImage);
	etmButtonSprite.setTexture(etmButtonTexture);
	etmButtonSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));

	generalButtonImage.loadFromFile("images/buttons/general.bmp");				//Button_general
	generalButtonTexture.loadFromImage(generalButtonImage);
	generalButtonSprite.setTexture(generalButtonTexture);
	generalButtonSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));

	terrainButtonImage.loadFromFile("images/buttons/terrain.bmp");				//Button_terrain
	terrainButtonTexture.loadFromImage(terrainButtonImage);
	terrainButtonSprite.setTexture(terrainButtonTexture);
	terrainButtonSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));

	buildingsButtonImage.loadFromFile("images/buttons/buildings.bmp");			//Button_buildings
	buildingsButtonTexture.loadFromImage(buildingsButtonImage);
	buildingsButtonSprite.setTexture(buildingsButtonTexture);
	buildingsButtonSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));

	mobsButtonImage.loadFromFile("images/buttons/mobs.bmp");					//Button_mobs
	mobsButtonTexture.loadFromImage(mobsButtonImage);
	mobsButtonSprite.setTexture(mobsButtonTexture);
	mobsButtonSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));

	startGameButtonImage.loadFromFile("images/buttons/start_game.bmp");				//Button_exit_to_menu
	startGameButtonTexture.loadFromImage(startGameButtonImage);
	startGameButtonSprite.setTexture(startGameButtonTexture);
	startGameButtonSprite.setTextureRect(sf::IntRect(0, 0, 266, 48));
}



int PreSettingsWindow::interact(sf::Vector2i& mouseCoord, bool& isMenuOpen)
{
	while (isMenuOpen)
	{


		if (LMB_Pressed)
		{
			if (etmButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
			{
				std::cout << "exit_to_menu_confirmed" << std::endl;
				return MAIN_MENU;
			}

			if (startGameButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
			{
				std::cout << "start_game" << std::endl;
				generalPreSettingsWindow.enterSettings();
				return GAMEPLAY;
			}

			if (generalButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
			{
				std::cout << "general" << std::endl;
				generalPreSettingsWindow.setVisible(true);
				Sleep(150);

				//generalPreSettingsWindow.interact(mouseCoord, isMenuOpen, event);
			}

			if (terrainButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
			{
				std::cout << "terrain" << std::endl;
				Sleep(150);
			}

			if (buildingsButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
			{
				std::cout << "buildings" << std::endl;
				Sleep(150);
			}

			if (mobsButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
			{
				std::cout << "mobs" << std::endl;
				Sleep(150);
			}

		}


		generalPreSettingsWindow.interact(mouseCoord, isMenuOpen);

		Sleep(16);
	}
}



void PreSettingsWindow::relocate(int windowSizeX, int windowSizeY)
{
	positionX = (windowSizeX - sizeX) / 2;
	positionY = (windowSizeY - sizeY) / 2;
	//std::cout << " win x:" << positionX << " win y:" << positionY << '\n';

	etmButtonSprite.setPosition(positionX + sizeX - 58, positionY + 10);
	startGameButtonSprite.setPosition(positionX + (sizeX / 2) - 133, positionY + sizeY - 58);

	generalButtonSprite.setPosition(positionX + 10, positionY + 10);
	terrainButtonSprite.setPosition(positionX + 70, positionY + 10);
	buildingsButtonSprite.setPosition(positionX + 130, positionY + 10);
	mobsButtonSprite.setPosition(positionX + 190, positionY + 10);

	generalPreSettingsWindow.relocate(windowSizeX, windowSizeY);
}



void PreSettingsWindow::draw(sf::RenderWindow& window)
{
	if (isVisible)
	{
		this->drawSubWindowBase(window);
		window.draw(etmButtonSprite);
		window.draw(startGameButtonSprite);

		window.draw(generalButtonSprite);
		window.draw(terrainButtonSprite);
		window.draw(buildingsButtonSprite);
		window.draw(mobsButtonSprite);

		generalPreSettingsWindow.draw(window);
	}
}
