#pragma once
#ifndef CONFIRMATION_H
#define CONFIRMATION_H

#include "sub_windows_util/sub_window.h"
#include "sub_windows_util/button/button.h"


class ConfirmationWindow : public SubWindow
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

	bool interact(sf::Vector2i& mouseCoord);
	void relocate(const sf::Vector2u wndowSize) override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};


#endif // CONFIRMATION_H
