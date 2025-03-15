
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


BuildingsPreSettingsPage::BuildingsPreSettingsPage(const sf::Vector2i position) : Page(sf::Vector2i(700, 350), position)
{
	this->prepareInterfaceSprites();
	this->relocateWithOwner(sf::Vector2i(40, 60));
	isVisible = false;
}

void BuildingsPreSettingsPage::prepareInterfaceSprites()
{
	const int line0 = 110;

	fields[DURABILITY] = TextField(sf::String(L"1"), 26, sf::Vector2i(line0, 40));
	fields[EXPENSES] = TextField(sf::String(L"1"), 26, sf::Vector2i(line0, 80));
	fields[CONSTRUCTION_SPEED] = TextField(sf::String(L"1"), 26, sf::Vector2i(line0, 125));

	tDurability = sf::Text(turretClassic, sf::String(L"Множитель\nпрочности"), 12);
	tExspenses = sf::Text(turretClassic, sf::String(L"Множитель\nстоимости"), 12);
	tConstructionSpeed = sf::Text(turretClassic, sf::String(L"Множитель\nскорости\nстроительства"), 12);
	tDurability.setFillColor(standardColor);
	tExspenses.setFillColor(standardColor);
	tConstructionSpeed.setFillColor(standardColor);
}

void BuildingsPreSettingsPage::interact()
{
	if (!isVisible)
		return;
	for (auto& field : fields)
		field.second.interact();
}

void BuildingsPreSettingsPage::enter(PreSettings& preSettings)
{
	preSettings.changeBuildings().maxDurabilityModifier = fields[DURABILITY].getValueUint32();
	preSettings.changeBuildings().expensesModifier = fields[EXPENSES].getValueUint32();
	preSettings.changeBuildings().constructionSpeedModifier = fields[CONSTRUCTION_SPEED].getValueUint32();
}

void BuildingsPreSettingsPage::relocateWithOwner(const sf::Vector2i ownerPosition)
{
	Page::relocateWithOwner(ownerPosition);
	for (auto& field : fields)
		field.second.relocateWithOwner(position);

	tDurability.setPosition(sf::Vector2f(position.x + 10, position.y + 40));
	tExspenses.setPosition(sf::Vector2f(position.x + 10, position.y + 80));
	tConstructionSpeed.setPosition(sf::Vector2f(position.x + 10, position.y + 120));
}

void BuildingsPreSettingsPage::draw(sf::RenderWindow& window)
{
	if (!isVisible)
		return;
	drawBase(window);
	for (auto& field : fields)
		field.second.draw(window);
	window.draw(tDurability);
	window.draw(tExspenses);
	window.draw(tConstructionSpeed);
}
