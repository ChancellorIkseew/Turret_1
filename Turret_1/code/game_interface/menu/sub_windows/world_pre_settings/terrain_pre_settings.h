#pragma once
#ifndef TERRAIN_PRE_SETTINGS
#define TERRAIN_PRE_SETTINGS

#include <SFML/Graphics.hpp>

#include "../../../gameplay/sub_windows/sub_windows_util/sub_window.h"


class TerrainPreSettingsWindow : public SubWindow
{
private:


public:

	TerrainPreSettingsWindow();
	~TerrainPreSettingsWindow() = default;

	void interact(sf::Vector2i& mouseCoord, bool& isMenuOpen);
	void relocate(int windowSizeX, int windowSizeY) override;

	void prepareInterfaceSprites() override;
	void draw(sf::RenderWindow& window) override;

};

extern TerrainPreSettingsWindow terrainPreSettingsWindow;


#endif // TERRAIN_PRE_SETTINGS
