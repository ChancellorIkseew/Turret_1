#pragma once
#ifndef SETTINGS_WINDOW_H
#define SETTINGS_WINDOW_H

#include <map>
#include "game_interface/ui_window/ui_window/ui_window.h"
#include "game_interface/ui_window/sub_win_types/text_field/text_field.h"

class SettingsWindow : public UIWindow
{
private:
	std::map<int, TextField> fields;


	SettingsWindow(const SettingsWindow&) = delete;
	SettingsWindow& operator=(const SettingsWindow&) = delete;
	void prepareInterfaceSprites() override final;

public:
	SettingsWindow();
	~SettingsWindow() = default;

	void interact(const bool& windowOpen);
	void relocate(const sf::Vector2i windowSize) override final;

	void draw(sf::RenderWindow& window) override final;

};

#endif // SETTINGS_H
