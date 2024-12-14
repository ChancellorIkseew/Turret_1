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
	std::map<int, sf::Text> texts;

public:
	MobsPreSettingsPage(const sf::Vector2u position);
	~MobsPreSettingsPage() = default;

	void interact() override final;
	void enter() override final;
	void relocateWithOwner(const sf::Vector2u windowSizeY) override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};

#endif // MENU_MOBS_PRE_SETTINGS
