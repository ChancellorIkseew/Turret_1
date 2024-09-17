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

public:

	ConfirmationWindow();
	~ConfirmationWindow();

	void prepareInterfaceSprites() override;

	void draw(sf::RenderWindow& window) override;

	bool interactWindow(sf::Vector2i& mouseCoord);

	void relocate(int windowSizeX, int windowSizeY) override;

};


#endif // CONFIRMATION_H
