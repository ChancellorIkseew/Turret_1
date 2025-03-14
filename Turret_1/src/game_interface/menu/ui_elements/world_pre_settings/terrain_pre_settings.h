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
	std::map<ResType, ResIco> resIco;
	std::map<ResType, TextField> frequency;
	std::map<ResType, TextField> depositSize;

	TextField seed;
	TextField smoothLayer;

	sf::Text tFrequency = sf::Text(turretClassic);
	sf::Text tDepositSize = sf::Text(turretClassic);
	sf::Text tSeed = sf::Text(turretClassic);
	sf::Text tSmoothLayer = sf::Text(turretClassic);

public:
	TerrainPreSettingsPage(const sf::Vector2i position);
	~TerrainPreSettingsPage() = default;

	void interact() override final;
	void enter(PreSettings& preSettings) override final;
	void relocateWithOwner(const sf::Vector2i windowSizeY) override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};

#endif // MENU_TERRAIN_PRE_SETTINGS
