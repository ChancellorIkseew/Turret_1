#pragma once
#ifndef MENU_GENERAL_PRE_SETTINGS
#define MENU_GENERAL_PRE_SETTINGS

#include <map>

#include "game_interface/ui_window/sub_win_types/page/page.h"
#include "game_interface/ui_window/sub_win_types/text_field/text_field.h"
#include "game_interface/ui_window/elements/res_ico/res_ico.h"


class GeneralPreSettingsPage : public Page
{
private:
	std::map<int, TextField> fields;
	std::map<int, ResIco> resIco;

public:
	GeneralPreSettingsPage(const sf::Vector2u position);
	~GeneralPreSettingsPage() = default;

	void interact(const sf::Vector2i& mouseCoord, bool& isMenuOpen) override final;
	void relocateWithOwner(const sf::Vector2u ownerPosition) override final;
	void enter() override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};

#endif // MENU_GENERAL_PRE_SETTINGS
