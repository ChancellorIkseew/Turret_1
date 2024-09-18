#pragma once
#ifndef CONFIRMATION_H
#define CONFIRMATION_H

#include "sub_windows_util/sub_window.h"


class ConfirmationWindow : public SubWindow
{
private:

	sf::Image confirmButtonImage;
	sf::Texture confirmButtonTexture;
	sf::Sprite confirmButtonSprite;

	sf::Image rejectButtonImage;
	sf::Texture rejectButtonTexture;
	sf::Sprite rejectButtonSprite;

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

	bool interactWindow(sf::Vector2i& mouseCoord);
	void relocate(int windowSizeX, int windowSizeY) override;

	void prepareInterfaceSprites() override;
	void draw(sf::RenderWindow& window) override;

};


#endif // CONFIRMATION_H
