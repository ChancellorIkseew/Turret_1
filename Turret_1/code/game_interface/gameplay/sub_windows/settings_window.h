#pragma once
#ifndef SETTINGS_WINDOW_H
#define SETTINGS_WINDOW_H

#include <SFML\Graphics.hpp>

#include "sub_windows_util/sub_window.h"


class SettingsWindow : public SubWindow
{
private:

	sf::Image confirmButtonImage;
	sf::Texture confirmButtonTexture;
	sf::Sprite confirmButtonSprite;

	sf::Image rejectButtonImage;
	sf::Texture rejectButtonTexture;
	sf::Sprite rejectButtonSprite;

	sf::Text confirmationText;

public:

	SettingsWindow();
	~SettingsWindow();

	void prepareInterfaceSprites() override;

	void draw(sf::RenderWindow& window) override;

	bool interact(sf::Vector2i& mouseCoord);

	void relocate(int windowSizeX, int windowSizeY) override;

};


#endif // SETTINGS_H
