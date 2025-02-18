
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

	fields[MAP_MAX_X] = TextField(sf::String(L"100"), 100, sf::Vector2u(10, 40));
	fields[MAP_MAX_Y] = TextField(sf::String(L"100"), 100, sf::Vector2u(10, 65));

	fields[RES_STONE] = TextField(sf::String(L"500"), 100, sf::Vector2u(line1, 40));
	fields[RES_IRON] = TextField(sf::String(L"1000"), 100, sf::Vector2u(line1, 65));
	fields[RES_COPPER] = TextField(sf::String(L"500"), 100, sf::Vector2u(line1, 90));
	fields[RES_SILICON] = TextField(sf::String(L"0"), 100, sf::Vector2u(line1, 115));
	fields[RES_COAL] = TextField(sf::String(L"0"), 100, sf::Vector2u(line1, 140));
	fields[RES_SULFUR] = TextField(sf::String(L"0"), 100, sf::Vector2u(line1, 165));

	resIco[RES_STONE] = ResIco(RES_STONE, sf::Vector2u(line0, 43));
	resIco[RES_IRON] = ResIco(RES_IRON, sf::Vector2u(line0, 68));
	resIco[RES_COPPER] = ResIco(RES_COPPER, sf::Vector2u(line0, 93));
	resIco[RES_SILICON] = ResIco(RES_SILICON, sf::Vector2u(line0, 118));
	resIco[RES_COAL] = ResIco(RES_COAL, sf::Vector2u(line0, 143));
	resIco[RES_SULFUR] = ResIco(RES_SULFUR, sf::Vector2u(line0, 168));
}

void GeneralPreSettingsPage::interact()
{
	if (isVisible)
	{
		for (auto& field : fields)
			field.second.interact();
	}
}

void GeneralPreSettingsPage::enter(std::any& data)
{
	std::any_cast<PreSettings>(data).changeTerrain().mapSize = {fields[MAP_MAX_X].getIntValue(), fields[MAP_MAX_Y].getIntValue()};

	std::map<int, int> startRes;
	for (auto& field : fields)
		startRes[field.first] = field.second.getIntValue();
	std::any_cast<PreSettings>(data).changeGeneral().startBalance = startRes;
}

void GeneralPreSettingsPage::relocateWithOwner(const sf::Vector2u ownerPosition)
{
	Page::relocateWithOwner(ownerPosition);
	for (auto& field : fields)
		field.second.relocateWithOwner(position);
	for (auto& ico : resIco)
		ico.second.relocate(position);
}

void GeneralPreSettingsPage::draw(sf::RenderWindow& window)
{
	if (isVisible)
	{
		drawBase(window);
		for (auto& field : fields)
			field.second.draw(window);
		for (auto& ico : resIco)
			ico.second.draw(window);
	}
}
