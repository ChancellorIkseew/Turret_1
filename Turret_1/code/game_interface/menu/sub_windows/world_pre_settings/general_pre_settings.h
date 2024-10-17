#pragma once
#ifndef GENERAL_PRE_SETTINGS
#define GENERAL_PRE_SETTINGS

#include <map>

#include "game_interface/sub_window/sub_win_types/page/page.h"
#include "game_interface/sub_window/sub_win_types/text_field/text_field.h"
#include "game_interface/sub_window/elements/res_ico/res_ico.h"


class GeneralPreSettingsWindow : public Page
{
private:
	std::map<int, TextField> fields;
	std::map<int, ResIco> resIco;

public:
	GeneralPreSettingsWindow(const sf::Vector2u position);
	~GeneralPreSettingsWindow() = default;

	void interact(const sf::Vector2i& mouseCoord, bool& isMenuOpen) override final;
	void relocate(const sf::Vector2u ownerPosition) override final;
	void enter() override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};

#endif // GENERAL_PRE_SETTINGS
