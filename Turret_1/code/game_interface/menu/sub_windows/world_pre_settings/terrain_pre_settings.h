#pragma once
#ifndef TERRAIN_PRE_SETTINGS
#define TERRAIN_PRE_SETTINGS

#include <SFML/Graphics.hpp>

#include "../../../gameplay/sub_windows/sub_windows_util/sub_window.h"


class TerrainPreSettingsWindow : public SubWindow
{
private:

	sf::Image etmButtonImage;
	sf::Texture etmButtonTexture;
	sf::Sprite etmButtonSprite;

	sf::Image generalButtonImage;
	sf::Texture generalButtonTexture;
	sf::Sprite generalButtonSprite;

	sf::Image terrainButtonImage;
	sf::Texture terrainButtonTexture;
	sf::Sprite terrainButtonSprite;

	sf::Image buildingsButtonImage;
	sf::Texture buildingsButtonTexture;
	sf::Sprite buildingsButtonSprite;

	sf::Image mobsButtonImage;
	sf::Texture mobsButtonTexture;
	sf::Sprite mobsButtonSprite;

public:

	TerrainPreSettingsWindow();

	void prepareInterfaceSprites() override;

	void interact(sf::Vector2i& mouseCoord, bool& isMenuOpen);

	void relocate(int windowSizeX, int windowSizeY) override;

	void draw(sf::RenderWindow& window) override;

	~TerrainPreSettingsWindow();

};

extern TerrainPreSettingsWindow terrainPreSettingsWindow;


#endif // TERRAIN_PRE_SETTINGS
