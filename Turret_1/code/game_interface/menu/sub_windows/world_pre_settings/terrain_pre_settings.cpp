
#include <iostream>

#include "terrain_pre_settings.h"

#include "game_interface/system/system.h"


TerrainPreSettingsWindow::TerrainPreSettingsWindow() : SubWindow('s', 400, 700, 100, 100)
{
	this->prepareInterfaceSprites();
}



void TerrainPreSettingsWindow::prepareInterfaceSprites()
{

}



void TerrainPreSettingsWindow::interact(sf::Vector2i& mouseCoord, bool& isMenuOpen)
{







	//if (generalButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
	//{
		//std::cout << "general" << std::endl;
		//Sleep(150);
	//}
}



void TerrainPreSettingsWindow::relocate(int windowSizeX, int windowSizeY)
{

}



void TerrainPreSettingsWindow::draw(sf::RenderWindow& window)
{

}
