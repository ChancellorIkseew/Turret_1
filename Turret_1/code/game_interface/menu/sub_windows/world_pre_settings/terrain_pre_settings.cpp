 
#include "terrain_pre_settings.h"

#include "game_interface/system/system.h"
#include "map_structures/resources/res_enum.h"
#include "game_interface/sub_window/sub_win_util/fonts.h"
#include "map_structures/pre-settings/pre-settings.h"


TerrainPreSettingsWindow::TerrainPreSettingsWindow(const sf::Vector2u position) : Page(sf::Vector2u(700, 350), position)
{
	this->prepareInterfaceSprites();
	isVisible = false;
}

void TerrainPreSettingsWindow::prepareInterfaceSprites()
{
	int line1 = 150;
	int line2 = 300;

	tFrequency = sf::Text(sf::String(L"Частота"), turretClassic, 16);
	tDepositSize= sf::Text(sf::String(L"Размер"), turretClassic, 16);
	tFrequency.setFillColor(standardColor);
	tDepositSize.setFillColor(standardColor);

	frequency[RES_STONE] = TextField(sf::String(L"10"), sf::Vector2u(100, 23), sf::Vector2u(line1, 40));
	frequency[RES_IRON] = TextField(sf::String(L"10"), sf::Vector2u(100, 23), sf::Vector2u(line1, 65));
	frequency[RES_COPPER] = TextField(sf::String(L"10"), sf::Vector2u(100, 23), sf::Vector2u(line1, 90));
	frequency[RES_SILICON] = TextField(sf::String(L"10"), sf::Vector2u(100, 23), sf::Vector2u(line1, 115));
	frequency[RES_COAL] = TextField(sf::String(L"10"), sf::Vector2u(100, 23), sf::Vector2u(line1, 140));
	frequency[RES_SULFUR] = TextField(sf::String(L"10"), sf::Vector2u(100, 23), sf::Vector2u(line1, 165));

	depositSize[RES_STONE] = TextField(sf::String(L"10"), sf::Vector2u(100, 23), sf::Vector2u(line2, 40));
	depositSize[RES_IRON] = TextField(sf::String(L"10"), sf::Vector2u(100, 23), sf::Vector2u(line2, 65));
	depositSize[RES_COPPER] = TextField(sf::String(L"10"), sf::Vector2u(100, 23), sf::Vector2u(line2, 90));
	depositSize[RES_SILICON] = TextField(sf::String(L"10"), sf::Vector2u(100, 23), sf::Vector2u(line2, 115));
	depositSize[RES_COAL] = TextField(sf::String(L"10"), sf::Vector2u(100, 23), sf::Vector2u(line2, 140));
	depositSize[RES_SULFUR] = TextField(sf::String(L"10"), sf::Vector2u(100, 23), sf::Vector2u(line2, 165));

}

void TerrainPreSettingsWindow::interact(const sf::Vector2i& mouseCoord, bool& isMenuOpen)
{
	if (isVisible)
	{
		for (auto& field : frequency)
		{
			field.second.interact(mouseCoord);
		}

		for (auto& field : depositSize)
		{
			field.second.interact(mouseCoord);
		}
	}
}

void TerrainPreSettingsWindow::enter()
{
	std::map<int, int> iFrequency;
	std::map<int, int> iDepositSize;

	for (auto& field : frequency)
	{
		iFrequency[field.first] = field.second.getIntValue();
	}

	for (auto& field : depositSize)
	{
		iDepositSize[field.first] = field.second.getIntValue();
	}

	PreSettings::getTerrain().frequency = iFrequency;
	PreSettings::getTerrain().depositSize = iDepositSize;
}

void TerrainPreSettingsWindow::relocate(const sf::Vector2u ownerPosition)
{
	Page::relocate(ownerPosition);
	tFrequency.setPosition(position.x + 165, position.y + 20);
	tDepositSize.setPosition(position.x + 315, position.y + 20);

	for (auto& field : frequency)
	{
		field.second.relocate(position);
	}

	for (auto& field : depositSize)
	{
		field.second.relocate(position);
	}
}

void TerrainPreSettingsWindow::draw(sf::RenderWindow& window)
{
	if (isVisible)
	{
		this->drawSubWindowBase(window);
		window.draw(tFrequency);
		window.draw(tDepositSize);

		for (auto& field : frequency)
		{
			field.second.draw(window);
		}

		for (auto& field : depositSize)
		{
			field.second.draw(window);
		}
	}
}
