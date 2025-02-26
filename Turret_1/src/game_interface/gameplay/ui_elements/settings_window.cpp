
#include <iostream>
#include <sstream>

#include "settings_window.h"

#include "game_interface/ui_window/sub_win_util/fonts.h"
#include "game_interface/settings/settings.h"
#include "game_interface/main_window/main_window_resize.h"
#include "t1_system/input/input_handler.h"


SettingsWindow::SettingsWindow() : UIWindow(sf::Vector2u(720, 4800), sf::Vector2u(0, 0))
{
	this->prepareInterfaceSprites();
	isVisible = false;
}


void SettingsWindow::prepareInterfaceSprites()
{
	confirmButtonImage.loadFromFile("images/buttons/confirm.bmp");
	confirmButtonTexture.loadFromImage(confirmButtonImage);
	confirmButtonSprite.setTexture(confirmButtonTexture);
	confirmButtonSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));

	rejectButtonImage.loadFromFile("images/buttons/reject.bmp");
	rejectButtonTexture.loadFromImage(rejectButtonImage);
	rejectButtonSprite.setTexture(rejectButtonTexture);
	rejectButtonSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));

	confirmationText.setFont(turretClassic);
	confirmationText.setString(sf::String(L"Выйти без\nсохранения?"));
	confirmationText.setCharacterSize(16);
	confirmationText.setFillColor(sf::Color(180, 52, 52));
}


bool SettingsWindow::interact()
{
	while (true)
	{
		if (InputHandler::jactive(t1::BindName::LMB))
		{
			/*
			if (confirmButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
			{
				std::cout << "exit_confirmed" << std::endl;
				return true;
			}

			if (rejectButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
			{
				std::cout << "exit_was_rejected" << std::endl;
				return false;
			}
			*/
		}
	}
}


void SettingsWindow::relocate(const sf::Vector2u windowSize)
{
	relocateCentral(windowSize);
	confirmButtonSprite.setPosition(position.x + 10, position.y + 10);
	rejectButtonSprite.setPosition(position.x + 70, position.y + 10);
	confirmationText.setPosition(position.x + 10, position.y + 60);
}


void SettingsWindow::draw(sf::RenderWindow& window)
{
	if (isVisible)
	{
		drawBase(window);
		window.draw(confirmButtonSprite);
		window.draw(rejectButtonSprite);
		window.draw(confirmationText);
	}
}
