
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
	BLAST_DAMAGE = 5
};


MobsPreSettingsPage::MobsPreSettingsPage(const sf::Vector2i position) : Page(sf::Vector2i(700, 350), position)
{
	this->prepareInterfaceSprites();
	this->relocateWithOwner(sf::Vector2i(40, 60));
	isVisible = false;
}

void MobsPreSettingsPage::prepareInterfaceSprites()
{
	const int line0 = 95;
	const int line1 = 225;

	fields[QUANTITY] = TextField(1, 42, sf::Vector2i(line0, 45));
	fields[DURABILITY] = TextField(1.0f, 42, sf::Vector2i(line0, 95));
	fields[VI_LEVEL] = TextField(1, 42, sf::Vector2i(line0, 145));
	fields[COLLISION_DAMAGE] = TextField(1.0f, 42, sf::Vector2i(line0, 195));
	fields[DIRECT_DAMAGE] = TextField(1.0f, 42, sf::Vector2i(line1, 55));
	fields[BLAST_DAMAGE] = TextField(1.0f, 42, sf::Vector2i(line1, 105));

	quantity = sf::Text(turretClassic, sf::String(L"Множитель\nчисленности\nврагов"), 12);
	durabity = sf::Text(turretClassic, sf::String(L"Множитель\nпрочности\nмобов"), 12);
	VILevel = sf::Text(turretClassic, sf::String(L"Уровень\nинтеллекта\nмобов"), 12);
	collisionDamage = sf::Text(turretClassic, sf::String(L"Множитель\nконтактного\nурона мобов"), 12);
	directDamage = sf::Text(turretClassic, sf::String(L"Множитель\nурона от\nпопадания\nснарядов"), 12);
	blastDamage = sf::Text(turretClassic, sf::String(L"Множитель\nвзрывного\nурона"), 12);
	
	quantity.setFillColor(standardColor);
	durabity.setFillColor(standardColor);
	VILevel.setFillColor(standardColor);
	collisionDamage.setFillColor(standardColor);
	directDamage.setFillColor(standardColor);
	blastDamage.setFillColor(standardColor);
}

void MobsPreSettingsPage::interact()
{
	if (!isVisible)
		return;
	for (auto& field : fields)
		field.second.interact();
}

void MobsPreSettingsPage::enter(PreSettings& preSettings)
{
	preSettings.changeMobs().quantityModifier = fields[QUANTITY].getValueUint32();
	preSettings.changeMobs().maxDurabilityModifier = fields[DURABILITY].getValueFloat();
	preSettings.changeMobs().virtIntLevel = fields[VI_LEVEL].getValueUint32();
	preSettings.changeMobs().collisionDamageModifier = fields[COLLISION_DAMAGE].getValueFloat();
	preSettings.changeShells().directDamageModifier = fields[DIRECT_DAMAGE].getValueFloat();
	preSettings.changeShells().blastDamageModifier = fields[BLAST_DAMAGE].getValueFloat();
}

void MobsPreSettingsPage::relocateWithOwner(const sf::Vector2i ownerPosition)
{
	Page::relocateWithOwner(ownerPosition);
	for (auto& field : fields)
		field.second.relocateWithOwner(position);
	quantity.setPosition(sf::Vector2f(position.x + 10, position.y + 40));
	durabity.setPosition(sf::Vector2f(position.x + 10, position.y + 90));
	VILevel.setPosition(sf::Vector2f(position.x + 10, position.y + 140));
	collisionDamage.setPosition(sf::Vector2f(position.x + 10, position.y + 190));
	directDamage.setPosition(sf::Vector2f(position.x + 150, position.y + 40));
	blastDamage.setPosition(sf::Vector2f(position.x + 150, position.y + 100));
}

void MobsPreSettingsPage::draw(sf::RenderWindow& window)
{
	if (!isVisible)
		return;
	drawBase(window);
	for (auto& field : fields)
		field.second.draw(window);
	window.draw(quantity);
	window.draw(durabity);
	window.draw(VILevel);
	window.draw(collisionDamage);
	window.draw(directDamage);
	window.draw(blastDamage);
}
