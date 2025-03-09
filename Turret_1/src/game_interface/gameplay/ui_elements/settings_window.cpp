
#include "settings_window.h"

#include "game_interface/ui_window/sub_win_util/fonts.h"
#include "game_interface/settings/settings.h"
#include "game_interface/main_window/main_window_resize.h"
#include "t1_system/input/input_handler.h"


SettingsWindow::SettingsWindow() : UIWindow(sf::Vector2i(720, 4800))
{
	this->prepareInterfaceSprites();
	isVisible = false;
}


void SettingsWindow::prepareInterfaceSprites()
{
	//confirmationText.setFont(turretClassic);
	//confirmationText.setString(sf::String(L"Выйти без\nсохранения?"));
	//confirmationText.setCharacterSize(16);
	//confirmationText.setFillColor(sf::Color(180, 52, 52));
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


void SettingsWindow::relocate(const sf::Vector2i windowSize)
{
	
}


void SettingsWindow::draw(sf::RenderWindow& window)
{
	if (!isVisible)
		return;
	
}
