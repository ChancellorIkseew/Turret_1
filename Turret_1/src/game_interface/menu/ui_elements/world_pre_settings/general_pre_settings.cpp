
#include "general_pre_settings.h"
#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/resources/res_enum.h"

enum fieldEnum
{
	MAP_MAX_X = 10000,
	MAP_MAX_Y = 10001
};


GeneralPreSettingsPage::GeneralPreSettingsPage(const sf::Vector2i position) : Page(sf::Vector2i(700, 350), position)
{
	this->prepareInterfaceSprites();
	this->relocateWithOwner(sf::Vector2i(40, 60));
	isVisible = false;
}

void GeneralPreSettingsPage::prepareInterfaceSprites()
{
	const int line0 = 280;
	const int line1 = 300;

	mapSize[MAP_MAX_X] = TextField(100, 42, sf::Vector2i(10, 40));
	mapSize[MAP_MAX_Y] = TextField(100, 42, sf::Vector2i(10, 65));

	balance[ResType::STONE] = TextField(500, 100, sf::Vector2i(line1, 40));
	balance[ResType::IRON] = TextField(1000, 100, sf::Vector2i(line1, 65));
	balance[ResType::COPPER] = TextField(500, 100, sf::Vector2i(line1, 90));
	balance[ResType::SILICON] = TextField(0, 100, sf::Vector2i(line1, 115));
	balance[ResType::COAL] = TextField(0, 100, sf::Vector2i(line1, 140));
	balance[ResType::SULFUR] = TextField(0, 100, sf::Vector2i(line1, 165));

	resIco[ResType::STONE] = ResIco(ResType::STONE, sf::Vector2i(line0, 43));
	resIco[ResType::IRON] = ResIco(ResType::IRON, sf::Vector2i(line0, 68));
	resIco[ResType::COPPER] = ResIco(ResType::COPPER, sf::Vector2i(line0, 93));
	resIco[ResType::SILICON] = ResIco(ResType::SILICON, sf::Vector2i(line0, 118));
	resIco[ResType::COAL] = ResIco(ResType::COAL, sf::Vector2i(line0, 143));
	resIco[ResType::SULFUR] = ResIco(ResType::SULFUR, sf::Vector2i(line0, 168));
}

void GeneralPreSettingsPage::interact()
{
	if (!isVisible)
		return;
	for (auto& field : mapSize)
		field.second.interact();
	for (auto& field : balance)
		field.second.interact();
}

void GeneralPreSettingsPage::enter(PreSettings& preSettings)
{
	preSettings.changeTerrain().mapSize = TileCoord(mapSize[MAP_MAX_X].getValueUint32(), mapSize[MAP_MAX_Y].getValueUint32());
	preSettings.changeGeneral().gameMode = GameMode::SURVIVAL; // temporary

	std::map<ResType, uint32_t> startRes;
	for (auto& [resType, field] : balance)
		startRes[resType] = field.getValueUint32();
	preSettings.changeGeneral().startBalance = startRes;
}

void GeneralPreSettingsPage::relocateWithOwner(const sf::Vector2i ownerPosition)
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
	if (!isVisible)
		return;
	drawBase(window);
	for (auto& field : mapSize)
		field.second.draw(window);
	for (auto& field : balance)
		field.second.draw(window);
	for (auto& ico : resIco)
		ico.second.draw(window);
}
