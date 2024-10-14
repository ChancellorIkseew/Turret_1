#pragma once
#ifndef GENERAL_PRE_SETTINGS
#define GENERAL_PRE_SETTINGS

#include <SFML/Graphics.hpp>

#include "game_interface/sub_window/sub_win_types/page/page.h"
#include "game_interface/sub_window/sub_win_types/text_field/text_field.h"


class GeneralPreSettingsWindow : public Page
{
private:
	TextField mapMaxX, mapMaxY;

public:
	GeneralPreSettingsWindow(const sf::Vector2u position);
	~GeneralPreSettingsWindow() = default;

	void interact(const sf::Vector2i& mouseCoord, bool& isMenuOpen);
	void relocate(const sf::Vector2u ownerPosition) override final;
	void enterSettings();

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};

#endif // GENERAL_PRE_SETTINGS
