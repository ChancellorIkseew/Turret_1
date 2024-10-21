#pragma once
#ifndef MENU_TERRAIN_PRE_SETTINGS
#define MENU_TERRAIN_PRE_SETTINGS

#include <map>

#include "game_interface/ui_window/sub_win_types/page/page.h"
#include "game_interface/ui_window/elements/res_ico/res_ico.h"
#include "game_interface/ui_window/sub_win_types/text_field/text_field.h"


class TerrainPreSettingsPage : public Page
{
private:
	std::map<int, ResIco> resIco;
	std::map<int, TextField> frequency;
	std::map<int, TextField> depositSize;

	TextField seed;
	TextField smoothLayer;

	sf::Text tFrequency;
	sf::Text tDepositSize;
	sf::Text tSeed;
	sf::Text tSmoothLayer;

public:
	TerrainPreSettingsPage(const sf::Vector2u position);
	~TerrainPreSettingsPage() = default;

	void interact(const sf::Vector2i& mouseCoord, bool& isMenuOpen) override final;
	void enter() override final;
	void relocateWithOwner(const sf::Vector2u windowSizeY) override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};

#endif // MENU_TERRAIN_PRE_SETTINGS
