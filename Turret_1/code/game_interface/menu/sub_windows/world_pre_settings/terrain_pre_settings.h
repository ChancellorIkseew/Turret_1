#pragma once
#ifndef TERRAIN_PRE_SETTINGS
#define TERRAIN_PRE_SETTINGS

#include <SFML/Graphics.hpp>
#include "game_interface/sub_window/sub_win_types/page/page.h"


class TerrainPreSettingsWindow : public Page
{
public:
	TerrainPreSettingsWindow(const sf::Vector2u position);
	~TerrainPreSettingsWindow() = default;

	void interact(const sf::Vector2i& mouseCoord, bool& isMenuOpen);
	void relocate(const sf::Vector2u windowSizeY) override;

	void prepareInterfaceSprites() override;
	void draw(sf::RenderWindow& window) override;

};

#endif // TERRAIN_PRE_SETTINGS
