
#include "general_pre_settings.h"
#include "map_structures/pre-settings/pre-settings.h"


GeneralPreSettingsWindow::GeneralPreSettingsWindow() : SubWindow('s', 700, 350, 100, 100)
{
	this->prepareInterfaceSprites();
	isVisible = false;
}



void GeneralPreSettingsWindow::prepareInterfaceSprites()
{
	mapMaxX.setText(L"100");
	mapMaxY.setText(L"100");
}



void GeneralPreSettingsWindow::interact(sf::Vector2i& mouseCoord, bool& isMenuOpen)
{
	if (isVisible)
	{
		mapMaxX.interact(mouseCoord);
		mapMaxY.interact(mouseCoord);
	}
}



void GeneralPreSettingsWindow::relocate(int windowSizeX, int windowSizeY)
{
	positionX = (windowSizeX - sizeX) / 2;
	positionY = (windowSizeY - sizeY) / 2 ;

	mapMaxX.setPosition(positionX + 10, positionY + 40);
	mapMaxY.setPosition(positionX + 10, positionY + 65);
}



void GeneralPreSettingsWindow::draw(sf::RenderWindow& window)
{
	if (isVisible)
	{
		this->drawSubWindowBase(window);

		mapMaxX.draw(window);
		mapMaxY.draw(window);
	}
}



void GeneralPreSettingsWindow::enterSettings()
{
	PreSettings::setMapMaxX(mapMaxX.getIntValue());
	PreSettings::setMapMaxY(mapMaxY.getIntValue());
}
