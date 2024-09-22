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

	SettingsWindow();
	SettingsWindow(const SettingsWindow&) = delete;
	SettingsWindow& operator=(const SettingsWindow&) = delete;
	~SettingsWindow() = default;

public:

	static SettingsWindow& getInstance()
	{
		static SettingsWindow self;
		return self;
	}

	bool interact(sf::Vector2i& mouseCoord);
	void relocate(int windowSizeX, int windowSizeY) override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};


#endif // SETTINGS_H
