#pragma once
#ifndef SETTINGS_WINDOW_H
#define SETTINGS_WINDOW_H

#include "game_interface/ui_window/ui_window/ui_window.h"


class SettingsWindow : public UIWindow
{
private:
	SettingsWindow(const SettingsWindow&) = delete;
	SettingsWindow& operator=(const SettingsWindow&) = delete;
	void prepareInterfaceSprites() override final;

public:
	SettingsWindow();
	~SettingsWindow() = default;

	bool interact();
	void relocate(const sf::Vector2i windowSize) override final;

	void draw(sf::RenderWindow& window) override final;

};

#endif // SETTINGS_H
