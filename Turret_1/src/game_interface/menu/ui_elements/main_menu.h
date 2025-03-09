#pragma once
#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <map>
#include <SFML/Graphics.hpp>

#include "game_interface/main_window/game_state.h"
#include "game_interface/ui_window/ui_window/ui_window.h"
#include "game_interface/ui_window/elements/button/button.h"


class MainMenu : public UIWindow
{
private:
	std::map<int, Button> buttons;

public:
	MainMenu();
	~MainMenu() = default;

	GameState interact(bool& isMenuOpen);
	void relocate(const sf::Vector2i windowSizeY) override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};

#endif // MAIN_MENU_H
