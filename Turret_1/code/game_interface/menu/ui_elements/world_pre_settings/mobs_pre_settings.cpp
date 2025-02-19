
#include "mobs_pre_settings.h"
#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/resources/res_enum.h"
#include "game_interface/ui_window/sub_win_util/fonts.h"

enum fieldEnum
{
	QUANTITY = 0,
	DURABILITY = 1,
	COLLISION_DAMAGE = 2,
	VI_LEVEL = 3,
	DIRECT_DAMAGE = 4,
	BURST_DAMAGE = 5
};


MobsPreSettingsPage::MobsPreSettingsPage(const sf::Vector2u position) : Page(sf::Vector2u(700, 350), position)
{
	this->prepareInterfaceSprites();
	this->relocateWithOwner(sf::Vector2u(40, 60));
	isVisible = false;
}

void MobsPreSettingsPage::prepareInterfaceSprites()
{
	int line0 = 95;
	int line1 = 225;

	fields[QUANTITY] = TextField(sf::String(L"1"), 34, sf::Vector2u(line0, 45));
	fields[DURABILITY] = TextField(sf::String(L"1"), 34, sf::Vector2u(line0, 95));
	fields[VI_LEVEL] = TextField(sf::String(L"1"), 34, sf::Vector2u(line0, 145));
	fields[COLLISION_DAMAGE] = TextField(sf::String(L"1"), 34, sf::Vector2u(line0, 205));
	fields[DIRECT_DAMAGE] = TextField(sf::String(L"1"), 34, sf::Vector2u(line1, 55));
	fields[BURST_DAMAGE] = TextField(sf::String(L"1"), 34, sf::Vector2u(line1, 105));

	texts[QUANTITY] = sf::Text(sf::String(L"Множитель\nчисленности\nврагов"), turretClassic, 12);
	texts[DURABILITY] = sf::Text(sf::String(L"Множитель\nпрочности\nмобов"), turretClassic, 12);
	texts[VI_LEVEL] = sf::Text(sf::String(L"Уровень\nвиртуально\nинтеллекта\nмобов"), turretClassic, 12);
	texts[COLLISION_DAMAGE] = sf::Text(sf::String(L"Множитель\nконтактного\nурона мобов"), turretClassic, 12);
	texts[DIRECT_DAMAGE] = sf::Text(sf::String(L"Множитель\nурона от\nпопадания\nснарядов"), turretClassic, 12);
	texts[BURST_DAMAGE] = sf::Text(sf::String(L"Множитель\nвзрывного\nурона"), turretClassic, 12);
	
	for (auto& text : texts)
		text.second.setFillColor(standardColor);
}

void MobsPreSettingsPage::interact()
{
	if (isVisible)
	{
		for (auto& field : fields)
			field.second.interact();
	}
}

void MobsPreSettingsPage::enter(PreSettings& preSettings)
{
	preSettings.changeMobs().quantityModifier = fields[QUANTITY].getIntValue();
	preSettings.changeMobs().maxDurabilityModifier = fields[DURABILITY].getIntValue();
	preSettings.changeMobs().virtIntLevel = fields[VI_LEVEL].getIntValue();
	preSettings.changeMobs().collisionDamage = fields[COLLISION_DAMAGE].getIntValue();
	preSettings.changeShells().directDamageModifier = fields[DIRECT_DAMAGE].getIntValue();
	preSettings.changeShells().burstDamageModifier = fields[BURST_DAMAGE].getIntValue();
}

void MobsPreSettingsPage::relocateWithOwner(const sf::Vector2u ownerPosition)
{
	Page::relocateWithOwner(ownerPosition);
	for (auto& field : fields)
		field.second.relocateWithOwner(position);
	int deltaY = 40;
	for (int i = 0; i < 4; ++i)
	{
		texts[i].setPosition(position.x + 10, position.y + deltaY);
		deltaY += 50;
	}
	deltaY = 40;
	for (int i = 4; i < 6; ++i)
	{
		texts[i].setPosition(position.x + 150, position.y + deltaY);
		deltaY += 60;
	}
}

void MobsPreSettingsPage::draw(sf::RenderWindow& window)
{
	if (isVisible)
	{
		drawBase(window);
		for (auto& text : texts)
			window.draw(text.second);
		for (auto& field : fields)
			field.second.draw(window);
	}
}
