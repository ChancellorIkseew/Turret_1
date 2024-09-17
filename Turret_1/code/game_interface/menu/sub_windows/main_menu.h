#pragma once

#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <SFML/Graphics.hpp>
#include "../../gameplay/sub_windows/sub_windows_util/sub_window.h"


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

	void prepareInterfaceSprites() override;

	int interact(sf::Vector2i& mouseCoord, bool& isMenuOpen);

	void relocate(int windowSizeX, int windowSizeY) override;

	void draw(sf::RenderWindow& window) override;

	~MainMenu();

};

#endif // MAIN_MENU_H