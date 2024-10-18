 
#include "terrain_pre_settings.h"

#include "t1_system/system.h"
#include "map_structures/resources/res_enum.h"
#include "game_interface/ui_window/sub_win_util/fonts.h"
#include "map_structures/pre-settings/pre-settings.h"


TerrainPreSettingsPage::TerrainPreSettingsPage(const sf::Vector2u position) : Page(sf::Vector2u(700, 350), position)
{
	this->prepareInterfaceSprites();
	this->relocateWithOwner(sf::Vector2u(40, 60));
	isVisible = false;
}

void TerrainPreSettingsPage::prepareInterfaceSprites()
{
	int line0 = 425;
	int line1 = 445;
	int line2 = 500;

	tFrequency = sf::Text(sf::String(L"Частота"), turretClassic, 12);
	tDepositSize= sf::Text(sf::String(L"Размер"), turretClassic, 12);
	tSeed = sf::Text(sf::String(L"Ключ генерации"), turretClassic, 12);
	tSmoothLayer = sf::Text(sf::String(L"Уровень сглаживания"), turretClassic, 12);
	tFrequency.setFillColor(standardColor);
	tDepositSize.setFillColor(standardColor);
	tSeed.setFillColor(standardColor);
	tSmoothLayer.setFillColor(standardColor);

	frequency[RES_STONE] = TextField(sf::String(L"50"), 50, sf::Vector2u(line1, 40));
	frequency[RES_IRON] = TextField(sf::String(L"50"), 50, sf::Vector2u(line1, 65));
	frequency[RES_COPPER] = TextField(sf::String(L"50"), 50, sf::Vector2u(line1, 90));
	frequency[RES_SILICON] = TextField(sf::String(L"50"), 50, sf::Vector2u(line1, 115));
	frequency[RES_COAL] = TextField(sf::String(L"50"), 50, sf::Vector2u(line1, 140));
	frequency[RES_SULFUR] = TextField(sf::String(L"50"), 50, sf::Vector2u(line1, 165));

	depositSize[RES_STONE] = TextField(sf::String(L"10"), 50, sf::Vector2u(line2, 40));
	depositSize[RES_IRON] = TextField(sf::String(L"7"), 50, sf::Vector2u(line2, 65));
	depositSize[RES_COPPER] = TextField(sf::String(L"5"), 50, sf::Vector2u(line2, 90));
	depositSize[RES_SILICON] = TextField(sf::String(L"3"), 50, sf::Vector2u(line2, 115));
	depositSize[RES_COAL] = TextField(sf::String(L"3"), 50, sf::Vector2u(line2, 140));
	depositSize[RES_SULFUR] = TextField(sf::String(L"5"), 50, sf::Vector2u(line2, 165));

	resIco[RES_STONE] = ResIco(RES_STONE, sf::Vector2u(line0, 43));
	resIco[RES_IRON] = ResIco(RES_IRON, sf::Vector2u(line0, 68));
	resIco[RES_COPPER] = ResIco(RES_COPPER, sf::Vector2u(line0, 93));
	resIco[RES_SILICON] = ResIco(RES_SILICON, sf::Vector2u(line0, 118));
	resIco[RES_COAL] = ResIco(RES_COAL, sf::Vector2u(line0, 143));
	resIco[RES_SULFUR] = ResIco(RES_SULFUR, sf::Vector2u(line0, 168));

	seed = TextField(sf::String(L"0"), 90, sf::Vector2u(115, 40));
	smoothLayer = TextField(sf::String(L"0"), 18, sf::Vector2u(187, 65));
}

void TerrainPreSettingsPage::interact(const sf::Vector2i& mouseCoord, bool& isMenuOpen)
{
	if (isVisible)
	{
		for (auto& field : frequency)
			field.second.interact(mouseCoord);
		for (auto& field : depositSize)
			field.second.interact(mouseCoord);

		seed.interact(mouseCoord);
		smoothLayer.interact(mouseCoord);
	}
}

void TerrainPreSettingsPage::enter()
{
	std::map<int, int> iFrequency;
	std::map<int, int> iDepositSize;

	for (auto& field : frequency)
		iFrequency[field.first] = field.second.getIntValue();
	for (auto& field : depositSize)
		iDepositSize[field.first] = field.second.getIntValue();

	PreSettings::changeTerrain().frequency = iFrequency;
	PreSettings::changeTerrain().depositSize = iDepositSize;
	PreSettings::changeTerrain().seed = seed.getIntValue();
	PreSettings::changeTerrain().smoothLayer = smoothLayer.getIntValue();
}

void TerrainPreSettingsPage::relocateWithOwner(const sf::Vector2u ownerPosition)
{
	Page::relocateWithOwner(ownerPosition);
	tFrequency.setPosition(position.x + 445, position.y + 20);
	tDepositSize.setPosition(position.x + 500, position.y + 20);
	tSeed.setPosition(position.x + 10, position.y + 43);
	tSmoothLayer.setPosition(position.x + 10, position.y + 68);

	for (auto& field : frequency)
		field.second.relocateWithOwner(position);
	for (auto& field : depositSize)
		field.second.relocateWithOwner(position);
	for (auto& ico : resIco)
		ico.second.relocate(position);

	seed.relocateWithOwner(position);
	smoothLayer.relocateWithOwner(position);
}

void TerrainPreSettingsPage::draw(sf::RenderWindow& window)
{
	if (isVisible)
	{
		drawBase(window);
		window.draw(tFrequency);
		window.draw(tDepositSize);
		window.draw(tSeed);
		window.draw(tSmoothLayer);

		for (auto& field : depositSize)
			field.second.draw(window);
		for (auto& field : frequency)
			field.second.draw(window);
		for (auto& ico : resIco)
			ico.second.draw(window);

		seed.draw(window);
		smoothLayer.draw(window);
	}
}
