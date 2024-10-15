#pragma once
#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <map>
#include <SFML/Graphics.hpp>

#include "game_interface/sub_window/sub_window/sub_window.h"
#include "game_interface/sub_window/elements/button/button.h"


class MainMenu : public SubWindow
{
private:
	std::map<int, Button> buttons;

public:
	MainMenu();
	~MainMenu() = default;

	int interact(sf::Vector2i& mouseCoord, bool& isMenuOpen);
	void relocate(const sf::Vector2u windowSizeY) override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};

#endif // MAIN_MENU_H
