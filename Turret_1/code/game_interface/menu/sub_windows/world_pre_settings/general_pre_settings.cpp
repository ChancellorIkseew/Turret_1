
#include "general_pre_settings.h"
#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/resources/res_enum.h"

enum fieldEnum
{
	MAP_MAX_X = 10000,
	MAP_MAX_Y = 10001
};


GeneralPreSettingsWindow::GeneralPreSettingsWindow(const sf::Vector2u position) : Page(sf::Vector2u(700, 350), position)
{
	this->prepareInterfaceSprites();
	isVisible = false;
}

void GeneralPreSettingsWindow::prepareInterfaceSprites()
{
	fields[MAP_MAX_X] = TextField(sf::String(L"100"), sf::Vector2u(100, 23), sf::Vector2u(10, 40));
	fields[MAP_MAX_Y] = TextField(sf::String(L"100"), sf::Vector2u(100, 23), sf::Vector2u(10, 65));

	fields[RES_STONE] = TextField(sf::String(L"500"), sf::Vector2u(100, 23), sf::Vector2u(300, 40));
	fields[RES_IRON] = TextField(sf::String(L"1000"), sf::Vector2u(100, 23), sf::Vector2u(300, 65));
	fields[RES_COPPER] = TextField(sf::String(L"500"), sf::Vector2u(100, 23), sf::Vector2u(300, 90));
	fields[RES_SILICON] = TextField(sf::String(L"0"), sf::Vector2u(100, 23), sf::Vector2u(300, 115));
	fields[RES_COAL] = TextField(sf::String(L"0"), sf::Vector2u(100, 23), sf::Vector2u(300, 140));
	fields[RES_SULFUR] = TextField(sf::String(L"0"), sf::Vector2u(100, 23), sf::Vector2u(300, 165));
}

void GeneralPreSettingsWindow::interact(const sf::Vector2i& mouseCoord, bool& isMenuOpen)
{
	if (isVisible)
	{
		for (auto& field : fields)
		{
			field.second.interact(mouseCoord);
		}
	}
}

void GeneralPreSettingsWindow::enter()
{
	PreSettings::setMapSize({ fields[MAP_MAX_X].getIntValue(), fields[MAP_MAX_Y].getIntValue()});
	//PreSettings::setStartResources();
}

void GeneralPreSettingsWindow::relocate(const sf::Vector2u ownerPosition)
{
	Page::relocate(ownerPosition);
	for (auto& field : fields)
	{
		field.second.relocate(position);
	}
}

void GeneralPreSettingsWindow::draw(sf::RenderWindow& window)
{
	if (isVisible)
	{
		this->drawSubWindowBase(window);
		for (auto& field : fields)
		{
			field.second.draw(window);
		}
	}
}
