#pragma once
#ifndef PRE1
#define PRE1

#include <SFML/Graphics.hpp>
#include "game_interface/gameplay/sub_windows/sub_windows_util/sub_window.h"
#include "game_interface/gameplay/sub_windows/sub_windows_util/button/button.h"

#include "world_pre_settings/general_pre_settings.h"


class PreSettingsWindow : public SubWindow
{
private:
	Button startGame;
	Button exitToMenu;

	Button generalPreSettings;
	Button terrainPreSettings;
	Button buildingsPreSettings;
	Button mobsPreSettings;

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
