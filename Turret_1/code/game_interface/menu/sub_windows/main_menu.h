#pragma once
#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <SFML/Graphics.hpp>
#include "game_interface/gameplay/sub_windows/sub_windows_util/sub_window.h"


class MainMenu : public SubWindow
{
private:

	sf::Image playButtonImage;
	sf::Texture playButtonTexture;
	sf::Sprite playButtonSprite;

	sf::Image optionsButtonImage;
	sf::Texture optionsButtonTexture;
	sf::Sprite optionsButtonSprite;

public:

	MainMenu();
	~MainMenu() = default;

	int interact(sf::Vector2i& mouseCoord, bool& isMenuOpen);
	void relocate(int windowSizeX, int windowSizeY) override;

	void prepareInterfaceSprites() override;
	void draw(sf::RenderWindow& window) override;

};

#endif // MAIN_MENU_H
