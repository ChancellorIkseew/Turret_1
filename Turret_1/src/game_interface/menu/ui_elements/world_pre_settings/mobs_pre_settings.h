#pragma once
#ifndef MENU_MOBS_PRE_SETTINGS
#define MENU_MOBS_PRE_SETTINGS

#include <map>

#include "game_interface/ui_window/sub_win_types/page/page.h"
#include "game_interface/ui_window/sub_win_types/text_field/text_field.h"


class MobsPreSettingsPage : public Page
{
private:
	std::map<int, TextField> fields;
	sf::Text quantity = sf::Text(turretClassic);
	sf::Text durabity = sf::Text(turretClassic);
	sf::Text VILevel = sf::Text(turretClassic);
	sf::Text collisionDamage = sf::Text(turretClassic);
	sf::Text directDamage = sf::Text(turretClassic);
	sf::Text blastDamage = sf::Text(turretClassic);

public:
	MobsPreSettingsPage(const sf::Vector2i position);
	~MobsPreSettingsPage() = default;

	void interact() override final;
	void enter(PreSettings& preSettings) override final;
	void relocateWithOwner(const sf::Vector2i windowSizeY) override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};

#endif // MENU_MOBS_PRE_SETTINGS
