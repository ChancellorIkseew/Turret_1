#pragma once
#ifndef MENU_PRE_SETTINGS
#define MENU_PRE_SETTINGS

#include <map>
#include <SFML/Graphics.hpp>

#include "game_interface/ui_window/ui_window/ui_window.h"
#include "game_interface/ui_window/sub_win_types/page/page.h"
#include "game_interface/ui_window/elements/button/button.h"


class PreSettingsWindow : public UIWindow
{
private:
	std::map<int, Button> buttons;
	std::map<int, std::unique_ptr<Page>> pages;

public:
	PreSettingsWindow();
	~PreSettingsWindow() = default;

	int interact(bool& isMenuOpen);
	void relocate(sf::Vector2u windowSize) override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};

#endif // MENU_PRE_SETTINGS
