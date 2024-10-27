#pragma once
#ifndef CONFIRMATION_H
#define CONFIRMATION_H

#include "game_interface/ui_window/ui_window/ui_window.h"
#include "game_interface/ui_window/elements/button/button.h"


class ConfirmationWindow : public UIWindow
{
private:

	Button confirm;
	Button reject;

	sf::Text confirmationText;

	ConfirmationWindow();
	ConfirmationWindow(const ConfirmationWindow&) = delete;
	ConfirmationWindow& operator=(const ConfirmationWindow&) = delete;
	~ConfirmationWindow() = default;

public:

	static ConfirmationWindow& getInstance()
	{
		static ConfirmationWindow self;
		return self;
	}

	bool interact(const sf::Vector2i& mouseCoord);
	void relocate(const sf::Vector2u wndowSize) override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};

#endif // CONFIRMATION_H
