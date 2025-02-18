#pragma once
#ifndef MENU_BUILDINGS_PRE_SETTINGS
#define MENU_BUILDINGS_PRE_SETTINGS

#include <map>

#include "game_interface/ui_window/sub_win_types/page/page.h"
#include "game_interface/ui_window/sub_win_types/text_field/text_field.h"


class BuildingsPreSettingsPage : public Page
{
private:
	std::map<int, TextField> fields;
	sf::Text tDurability;
	sf::Text tExspenses;
	sf::Text tConstructionSpeed;

public:
	BuildingsPreSettingsPage(const sf::Vector2u position);
	~BuildingsPreSettingsPage() = default;

	void interact() override final;
	void relocateWithOwner(const sf::Vector2u ownerPosition) override final;
	void enter(std::any& data) override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};

#endif // MENU_BUILDINGS_PRE_SETTINGS
