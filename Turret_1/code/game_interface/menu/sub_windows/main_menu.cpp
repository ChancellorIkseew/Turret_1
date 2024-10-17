
#include "main_menu.h"

#include "t1_system/sleep.h"
#include "game_interface/main_window/main_window.h"

enum buttonsEnum
{
	PLAY = 0,
	EXIT_GAME = 1,
	SETTINGS = 2
};


MainMenu::MainMenu() : SubWindow('s', sf::Vector2u(720, 480), sf::Vector2u(0, 0))
{
	this->prepareInterfaceSprites();
	this->relocate(sf::Vector2u(800, 600));
}

void MainMenu::prepareInterfaceSprites()
{
	buttons[PLAY] = Button("play.bmp", sf::Vector2i(162, 48), sf::Vector2i(10, 10));
	buttons[EXIT_GAME] = Button("exit_to_menu.bmp", sf::Vector2i(48, 48), sf::Vector2i(70, 70));
	buttons[SETTINGS] = Button("settings.bmp", sf::Vector2i(48, 48), sf::Vector2i(10, 70));
}

int MainMenu::interact(sf::Vector2i& mouseCoord, bool& isMenuOpen)
{
	while (isMenuOpen)
	{
		if (buttons[PLAY].press(mouseCoord))
			return CHOISE_FOLDER_MENU;

		if (buttons[EXIT_GAME].press(mouseCoord))
			return EXIT;

		if (buttons[SETTINGS].press(mouseCoord))
			return OPTIONS;

		t1::system::sleep(16);
	}

	return MAIN_MENU;
}


void MainMenu::relocate(const sf::Vector2u windowSize)
{
	SubWindow::relocateCentral(windowSize);
	for (auto& btn : buttons)
	{
		btn.second.relocate(position);
	}
}


void MainMenu::draw(sf::RenderWindow& window)
{
	if (isVisible)
	{
		this->drawSubWindowBase(window);
		for (auto& btn : buttons)
		{
			btn.second.draw(window);
		}
	}
}
