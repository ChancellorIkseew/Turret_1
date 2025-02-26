
#include "general_pre_settings.h"
#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/resources/res_enum.h"

enum fieldEnum
{
	MAP_MAX_X = 10000,
	MAP_MAX_Y = 10001
};


GeneralPreSettingsPage::GeneralPreSettingsPage(const sf::Vector2u position) : Page(sf::Vector2u(700, 350), position)
{
	this->prepareInterfaceSprites();
	this->relocateWithOwner(sf::Vector2u(40, 60));
	isVisible = false;
}

void GeneralPreSettingsPage::prepareInterfaceSprites()
{
	int line0 = 280;
	int line1 = 300;

	mapSize[MAP_MAX_X] = TextField(sf::String(L"100"), 100, sf::Vector2u(10, 40));
	mapSize[MAP_MAX_Y] = TextField(sf::String(L"100"), 100, sf::Vector2u(10, 65));

	balance[ResType::STONE] = TextField(sf::String(L"500"), 100, sf::Vector2u(line1, 40));
	balance[ResType::IRON] = TextField(sf::String(L"1000"), 100, sf::Vector2u(line1, 65));
	balance[ResType::COPPER] = TextField(sf::String(L"500"), 100, sf::Vector2u(line1, 90));
	balance[ResType::SILICON] = TextField(sf::String(L"0"), 100, sf::Vector2u(line1, 115));
	balance[ResType::COAL] = TextField(sf::String(L"0"), 100, sf::Vector2u(line1, 140));
	balance[ResType::SULFUR] = TextField(sf::String(L"0"), 100, sf::Vector2u(line1, 165));

	resIco[ResType::STONE] = ResIco(ResType::STONE, sf::Vector2u(line0, 43));
	resIco[ResType::IRON] = ResIco(ResType::IRON, sf::Vector2u(line0, 68));
	resIco[ResType::COPPER] = ResIco(ResType::COPPER, sf::Vector2u(line0, 93));
	resIco[ResType::SILICON] = ResIco(ResType::SILICON, sf::Vector2u(line0, 118));
	resIco[ResType::COAL] = ResIco(ResType::COAL, sf::Vector2u(line0, 143));
	resIco[ResType::SULFUR] = ResIco(ResType::SULFUR, sf::Vector2u(line0, 168));
}

void GeneralPreSettingsPage::interact()
{
	if (isVisible)
	{
		for (auto& field : mapSize)
			field.second.interact();
		for (auto& field : balance)
			field.second.interact();
	}
}

void GeneralPreSettingsPage::enter(PreSettings& preSettings)
{
	preSettings.changeTerrain().mapSize = {mapSize[MAP_MAX_X].getIntValue(), mapSize[MAP_MAX_Y].getIntValue()};

	std::map<ResType, int> startRes;
	for (auto& field : balance)
		startRes[field.first] = field.second.getIntValue();
	preSettings.changeGeneral().startBalance = startRes;
}

void GeneralPreSettingsPage::relocateWithOwner(const sf::Vector2u ownerPosition)
{
	Page::relocateWithOwner(ownerPosition);
	for (auto& field : mapSize)
		field.second.relocateWithOwner(position);
	for (auto& field : balance)
		field.second.relocateWithOwner(position);
	for (auto& ico : resIco)
		ico.second.relocate(position);
}

void GeneralPreSettingsPage::draw(sf::RenderWindow& window)
{
	if (isVisible)
	{
		drawBase(window);
		for (auto& field : mapSize)
			field.second.draw(window);
		for (auto& field : balance)
			field.second.draw(window);
		for (auto& ico : resIco)
			ico.second.draw(window);
	}
}
