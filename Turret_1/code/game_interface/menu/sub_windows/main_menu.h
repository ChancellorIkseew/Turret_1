#pragma once
#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "game_interface/gameplay/sub_windows/sub_windows_util/sub_window.h"
#include "game_interface/gameplay/sub_windows/sub_windows_util/button/button.h"


class MainMenu : public SubWindow
{
private:
	std::vector<Button> buttons;

public:
	MainMenu();
	~MainMenu() = default;

	int interact(sf::Vector2i& mouseCoord, bool& isMenuOpen);
	void relocate(const sf::Vector2u windowSizeY) override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};

#endif // MAIN_MENU_H
