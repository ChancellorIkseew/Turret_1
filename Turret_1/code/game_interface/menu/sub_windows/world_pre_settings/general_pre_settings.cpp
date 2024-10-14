
#include "general_pre_settings.h"
#include "map_structures/pre-settings/pre-settings.h"


GeneralPreSettingsWindow::GeneralPreSettingsWindow() : Page(sf::Vector2u(700, 350), sf::Vector2u(100, 100))
{
	this->prepareInterfaceSprites();
	isVisible = false;
}



void GeneralPreSettingsWindow::prepareInterfaceSprites()
{
	mapMaxX.setText(L"100");
	mapMaxY.setText(L"100");
}



void GeneralPreSettingsWindow::interact(const sf::Vector2i& mouseCoord, bool& isMenuOpen)
{
	if (isVisible)
	{
		//mapMaxX.interact(mouseCoord);
		//mapMaxY.interact(mouseCoord);
	}
}



void GeneralPreSettingsWindow::relocate(const sf::Vector2u ownerPosition)
{
	Page::relocate(ownerPosition);
	mapMaxX.setPosition(sf::Vector2u(position.x + 10, position.y + 40));
	mapMaxY.setPosition(sf::Vector2u(position.x + 10, position.y + 65));
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
	PreSettings::setMapSize({ mapMaxX.getIntValue(), mapMaxY.getIntValue() });
}
