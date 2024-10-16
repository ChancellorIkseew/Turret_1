#pragma once
#ifndef TERRAIN_PRE_SETTINGS
#define TERRAIN_PRE_SETTINGS

#include <map>

#include "game_interface/sub_window/sub_win_types/page/page.h"
#include "game_interface/sub_window/sub_win_types/text_field/text_field.h"


class TerrainPreSettingsWindow : public Page
{
private:
	std::map<int, TextField> frequency;
	std::map<int, TextField> depositSize;

	sf::Text tFrequency;
	sf::Text tDepositSize;

public:
	TerrainPreSettingsWindow(const sf::Vector2u position);
	~TerrainPreSettingsWindow() = default;

	void interact(const sf::Vector2i& mouseCoord, bool& isMenuOpen) override final;
	void enter() override final;
	void relocate(const sf::Vector2u windowSizeY) override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};

#endif // TERRAIN_PRE_SETTINGS
