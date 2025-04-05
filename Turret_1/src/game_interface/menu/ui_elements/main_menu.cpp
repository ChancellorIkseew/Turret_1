
#include "main_menu.h"

#include "game_interface/main_window/main_window.h"
#include "t1_system/input/input_handler.h"
#include "t1_system/sleep.h"

enum buttonsEnum
{
	NEW_GAME = 0,
	LOAD_GAME = 1,
	EXIT_GAME = 2,
	SETTINGS = 3
};


MainMenu::MainMenu() : UIWindow(sf::Vector2i(720, 480), sf::Vector2i(0, 0))
{
	this->prepareInterfaceSprites();
}

void MainMenu::prepareInterfaceSprites()
{
	buttons[NEW_GAME] = Button("new_game.bmp", sf::Vector2i(242, 48), sf::Vector2i(10, 10));
	buttons[LOAD_GAME] = Button("load_game.bmp", sf::Vector2i(364, 48), sf::Vector2i(10, 68));
	buttons[EXIT_GAME] = Button("exit_to_menu.bmp", sf::Vector2i(48, 48), sf::Vector2i(70, 126));
	buttons[SETTINGS] = Button("settings.bmp", sf::Vector2i(48, 48), sf::Vector2i(10, 126));
}

GameState MainMenu::interact(bool& isMenuOpen)
{
	while (isMenuOpen)
	{
		if (buttons[NEW_GAME].press())
			return GameState::PRE_SETTINGS_MENU;
		if (buttons[LOAD_GAME].press())
			return GameState::CHOISE_FOLDER_MENU;
		if (buttons[EXIT_GAME].press())
			return GameState::EXIT;
		if (buttons[SETTINGS].press())
			return GameState::OPTIONS;
		t1::system::sleep(16);
	}
	return GameState::EXIT;
}


void MainMenu::relocate(const sf::Vector2i windowSize)
{
	relocateCentral(windowSize);
	for (auto& btn : buttons)
		btn.second.relocateWithOwner(position);
}


void MainMenu::draw(sf::RenderWindow& window)
{
	if (!isVisible)
		return;
	drawBase(window);
	for (auto& btn : buttons)
		btn.second.draw(window);
}
