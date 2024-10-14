#pragma once
#ifndef GENERAL_PRE_SETTINGS
#define GENERAL_PRE_SETTINGS

#include <SFML/Graphics.hpp>

#include "game_interface/gameplay/sub_windows/sub_windows_util/page/page.h"
#include "game_interface/gameplay/sub_windows/sub_windows_util/text_field.h"


class GeneralPreSettingsWindow : public Page
{
private:
	TextField mapMaxX, mapMaxY;

public:
	GeneralPreSettingsWindow();
	~GeneralPreSettingsWindow() = default;

	void interact(const sf::Vector2i& mouseCoord, bool& isMenuOpen);
	void relocate(const sf::Vector2u ownerPosition) override final;
	void enterSettings();

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};

#endif // GENERAL_PRE_SETTINGS
