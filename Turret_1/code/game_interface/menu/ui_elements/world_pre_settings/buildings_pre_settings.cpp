
#include "buildings_pre_settings.h"
#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/resources/res_enum.h"
#include "game_interface/ui_window/sub_win_util/fonts.h"

enum fieldEnum
{
	DURABILITY = 0,
	EXPENSES = 1,
	CONSTRUCTION_SPEED = 2,
};


BuildingsPreSettingsPage::BuildingsPreSettingsPage(const sf::Vector2u position) : Page(sf::Vector2u(700, 350), position)
{
	this->prepareInterfaceSprites();
	this->relocateWithOwner(sf::Vector2u(40, 60));
	isVisible = false;
}

void BuildingsPreSettingsPage::prepareInterfaceSprites()
{
	int line0 = 110;

	fields[DURABILITY] = TextField(sf::String(L"1"), 26, sf::Vector2u(line0, 40));
	fields[EXPENSES] = TextField(sf::String(L"1"), 26, sf::Vector2u(line0, 80));
	fields[CONSTRUCTION_SPEED] = TextField(sf::String(L"1"), 26, sf::Vector2u(line0, 125));

	tDurability = sf::Text(sf::String(L"Множитель\nпрочности"), turretClassic, 12);
	tExspenses = sf::Text(sf::String(L"Множитель\nстоимости"), turretClassic, 12);
	tConstructionSpeed = sf::Text(sf::String(L"Множитель\nскорости\nстроительства"), turretClassic, 12);
	tDurability.setFillColor(standardColor);
	tExspenses.setFillColor(standardColor);
	tConstructionSpeed.setFillColor(standardColor);
}

void BuildingsPreSettingsPage::interact()
{
	if (isVisible)
	{
		for (auto& field : fields)
			field.second.interact();
	}
}

void BuildingsPreSettingsPage::enter()
{
	PreSettings::changeBuildings().maxDurabilityModifier = fields[DURABILITY].getIntValue();
	PreSettings::changeBuildings().expensesModifier = fields[EXPENSES].getIntValue();
	PreSettings::changeBuildings().constructionSpeedModifier = fields[CONSTRUCTION_SPEED].getIntValue();
}

void BuildingsPreSettingsPage::relocateWithOwner(const sf::Vector2u ownerPosition)
{
	Page::relocateWithOwner(ownerPosition);
	for (auto& field : fields)
		field.second.relocateWithOwner(position);

	tDurability.setPosition(position.x + 10, position.y + 40);
	tExspenses.setPosition(position.x + 10, position.y + 80);
	tConstructionSpeed.setPosition(position.x + 10, position.y + 120);
}

void BuildingsPreSettingsPage::draw(sf::RenderWindow& window)
{
	if (isVisible)
	{
		drawBase(window);
		for (auto& field : fields)
			field.second.draw(window);

		window.draw(tDurability);
		window.draw(tExspenses);
		window.draw(tConstructionSpeed);
	}
}
