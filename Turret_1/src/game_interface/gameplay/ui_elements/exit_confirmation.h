#pragma once
#ifndef CONFIRMATION_H
#define CONFIRMATION_H

#include "game_interface/ui_window/ui_window/ui_window.h"
#include "game_interface/ui_window/elements/button/button.h"
#include "game_interface/ui_window/sub_win_util/fonts.h"

class ConfirmationWindow : public UIWindow
{
private:
	Button confirm;
	Button reject;

	sf::Text confirmationText = sf::Text(turretClassic);

	ConfirmationWindow(const ConfirmationWindow&) = delete;
	ConfirmationWindow& operator=(const ConfirmationWindow&) = delete;

public:
	ConfirmationWindow();
	~ConfirmationWindow() = default;

	bool interact();
	void relocate(const sf::Vector2i windowSize) override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};

#endif // CONFIRMATION_H
