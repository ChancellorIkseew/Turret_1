
#include "pre_settings.h"

#include "game_interface/system/sleep.h"
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
	startGame = Button("start_game.bmp", sf::Vector2i(266, 48), sf::Vector2i(70, 100));
	exitToMenu = Button("exit_to_menu.bmp", sf::Vector2i(48, 48), sf::Vector2i(10, 10));

	generalPreSettings = Button("general.bmp", sf::Vector2i(48, 48), sf::Vector2i(10, 10));
	terrainPreSettings = Button("terrain.bmp", sf::Vector2i(48, 48), sf::Vector2i(70, 10));
	buildingsPreSettings = Button("buildings.bmp", sf::Vector2i(48, 48), sf::Vector2i(130, 10));
	mobsPreSettings = Button("mobs.bmp", sf::Vector2i(48, 48), sf::Vector2i(190, 10));
}


int PreSettingsWindow::interact(sf::Vector2i& mouseCoord, bool& isMenuOpen)
{
	while (isMenuOpen)
	{
		if (startGame.press(mouseCoord))
		{
			generalPreSettingsWindow.enterSettings();
			return GAMEPLAY;
		}

		if (exitToMenu.press(mouseCoord))
			return MAIN_MENU;

		if (generalPreSettings.press(mouseCoord))
		{
			generalPreSettingsWindow.setVisible(true);
		}

		if (terrainPreSettings.press(mouseCoord))
		{

		}

		if (buildingsPreSettings.press(mouseCoord))
		{

		}

		if (mobsPreSettings.press(mouseCoord))
		{

		}

		generalPreSettingsWindow.interact(mouseCoord, isMenuOpen);

		t1::system::sleep(16);
	}
}



void PreSettingsWindow::relocate(int windowSizeX, int windowSizeY)
{
	positionX = (windowSizeX - sizeX) / 2;
	positionY = (windowSizeY - sizeY) / 2;
	
	startGame.relocate(sf::Vector2i(positionX, positionY));
	exitToMenu.relocate(sf::Vector2i(positionX, positionY));

	generalPreSettings.relocate(sf::Vector2i(positionX, positionY));
	terrainPreSettings.relocate(sf::Vector2i(positionX, positionY));
	buildingsPreSettings.relocate(sf::Vector2i(positionX, positionY));
	mobsPreSettings.relocate(sf::Vector2i(positionX, positionY));

	generalPreSettingsWindow.relocate(windowSizeX, windowSizeY);
}


void PreSettingsWindow::draw(sf::RenderWindow& window)
{
	if (isVisible)
	{
		this->drawSubWindowBase(window);
		startGame.draw(window);
		exitToMenu.draw(window);

		generalPreSettings.draw(window);
		terrainPreSettings.draw(window);
		buildingsPreSettings.draw(window);
		mobsPreSettings.draw(window);

		generalPreSettingsWindow.draw(window);
	}
}
