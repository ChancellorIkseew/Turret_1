#pragma once
#ifndef PRE1
#define PRE1

#include <SFML/Graphics.hpp>

#include "game_interface/gameplay/sub_windows/sub_windows_util/sub_window.h"

#include "world_pre_settings/general_pre_settings.h"


class PreSettingsWindow : public SubWindow
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

	sf::Image startGameButtonImage;
	sf::Texture startGameButtonTexture;
	sf::Sprite startGameButtonSprite;

	GeneralPreSettingsWindow generalPreSettingsWindow;

public:

	PreSettingsWindow();
	~PreSettingsWindow() = default;

	int interact(sf::Vector2i& mouseCoord, bool& isMenuOpen);
	void relocate(int windowSizeX, int windowSizeY) override;

	void prepareInterfaceSprites() override;
	void draw(sf::RenderWindow& window) override;

};


#endif // !PRE1
