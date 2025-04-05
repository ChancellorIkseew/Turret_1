
#include <iostream>
#include <SFML/Graphics.hpp>

#include "choise_save_folder.h"

#include "game_interface/ui_window/sub_win_util/fonts.h"
#include "t1_system/sleep.h"
#include "game_interface/main_window/main_window.h"

#include "map_structures/pre-settings/pre-settings.h"

enum buttonsEnum
{
	LOAD_GAME = 0,
	EXIT_TO_MENU = 1,
	LOAD_1 = 2,
};

std::string ChoiseFolderMenu::selectFolder(std::string v_saveFileName, bool& isFolderSelected)
{
	std::string saveFolderName;

	if (isFolderSelected == false)
	{
		saveFolderName = v_saveFileName;
		isFolderSelected = true;
	}
	else
	{
		saveFolderName = "0";
		isFolderSelected = false;
	}

	return saveFolderName;
}


ChoiseFolderMenu::ChoiseFolderMenu() : UIWindow(sf::Vector2i(720, 480), sf::Vector2i(0, 0))
{
	this->prepareInterfaceSprites();
	isVisible = false;

	isFolderSelected = false;
	isTextVisible = false;
}


void ChoiseFolderMenu::prepareInterfaceSprites()
{
	buttons[LOAD_GAME] = Button("load_game.bmp", sf::Vector2i(364, 48), sf::Vector2i(10, 68));
	buttons[EXIT_TO_MENU] = Button("exit_to_menu.bmp", sf::Vector2i(48, 48), sf::Vector2i(10, 10));

	helpText.setCharacterSize(16);
	helpText.setString(sf::String(L"„тобы начать игру, нужно выбрать сохранение,\nв которое будет записыватьс€ игровой прогресс."));
	helpText.setFillColor(darkRed);

	saves[LOAD_1] = SaveUI("save_1", sf::Vector2i(10, 126));
}


GameState ChoiseFolderMenu::interact(bool& isMenuOpen, std::string& saveFolderName)
{
	while (isMenuOpen)
	{
		/*
		if (buttons[LOAD_1].press())
		{
			saveFolderName = selectFolder("save_1", isFolderSelected);
			isTextVisible = false;
		}
		*/
		if (buttons[LOAD_GAME].press())
		{
			if (isFolderSelected)
				return GameState::GAMEPLAY;
			isTextVisible = true;
		}

		if (buttons[EXIT_TO_MENU].press())
			return GameState::MAIN_MENU;

		t1::system::sleep(16);
	}
	return GameState::EXIT;
}


void ChoiseFolderMenu::relocate(const sf::Vector2i windowSize)
{
	relocateCentral(windowSize);
	for (auto& [_, btn] : buttons)
		btn.relocateWithOwner(position);
	for (auto& [_, save] : saves)
		save.relocateWithOwner(position);

	helpText.setPosition(sf::Vector2f(position.x + 70, position.y + 350));
}


void ChoiseFolderMenu::draw(sf::RenderWindow& window)
{
	if (!isVisible)
		return;
	drawBase(window);
	for (auto& [_, btn] : buttons)
		btn.draw(window);
	for (auto& [_, save] : saves)
		save.draw(window);
	if (isTextVisible)
		window.draw(helpText);
}
