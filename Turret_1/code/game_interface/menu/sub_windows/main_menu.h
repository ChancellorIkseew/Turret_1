#pragma once
#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <SFML/Graphics.hpp>
#include "game_interface/gameplay/sub_windows/sub_windows_util/sub_window.h"
#include "game_interface/gameplay/sub_windows/sub_windows_util/button/button.h"


class MainMenu : public SubWindow
{
private:
	Button play;
	Button settings;

public:
	MainMenu();
	~MainMenu() = default;

	int interact(sf::Vector2i& mouseCoord, bool& isMenuOpen);
	void relocate(int windowSizeX, int windowSizeY) override;

	void prepareInterfaceSprites() override;
	void draw(sf::RenderWindow& window) override;

};

#endif // MAIN_MENU_H
