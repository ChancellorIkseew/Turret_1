
#include <iostream>
#include <SFML/Graphics.hpp>

#include "choise_save_folder.h"

#include "game_interface/sub_window/sub_win_util/fonts.h"
#include "game_interface/system/sleep.h"
#include "game_interface/main_window/main_window.h"

#include "map_structures/pre-settings/pre-settings.h"

enum buttonsEnum
{
	NEW_GAME = 0,
	LOAD_GAME = 1,
	EXIT_TO_MENU = 2,
	LOAD_1 = 3,
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


ChoiseFolderMenu::ChoiseFolderMenu() : SubWindow('s', sf::Vector2u(720, 480), sf::Vector2u(100, 100))
{
	isFolderSelected = false;
	isTextVisible = false;
	this->prepareInterfaceSprites();
	this->relocate(sf::Vector2u(1920, 1080));
	isVisible = false;
}



void ChoiseFolderMenu::prepareInterfaceSprites()
{
	buttons.resize(4);
	buttons[NEW_GAME] = Button("new_game.bmp", sf::Vector2i(242, 48), sf::Vector2i(10, 100));
	buttons[LOAD_GAME] = Button("load_game.bmp", sf::Vector2i(364, 48), sf::Vector2i(10, 170));
	buttons[EXIT_TO_MENU] = Button("exit_to_menu.bmp", sf::Vector2i(48, 48), sf::Vector2i(10, 10));
	buttons[LOAD_1] = Button("choise_load.bmp", sf::Vector2i(48, 48), sf::Vector2i(10, 240));

	helpText.setFont(turretClassic);
	helpText.setString(sf::String(L"„тобы начать игру, нужно выбрать сохранение,\nв которое будет записыватьс€ игровой прогресс."));
	helpText.setCharacterSize(16);
	helpText.setFillColor(sf::Color(68, 52, 52));
}



int ChoiseFolderMenu::interact(sf::Vector2i& mouseCoord, bool& isMenuOpen, bool& startNewGame, std::string& saveFolderName)
{
	while (isMenuOpen)
	{
		if (buttons[LOAD_1].press(mouseCoord))
		{
			saveFolderName = selectFolder("save1", isFolderSelected);
			isTextVisible = false;
		}

		if (buttons[LOAD_GAME].press(mouseCoord))
		{
			if (isFolderSelected)
			{
				PreSettings preSettings1(saveFolderName);
				startNewGame = false;
				return GameCondition::GAMEPLAY;
			}
			else
			{
				isTextVisible = true;
			}
		}

		if (buttons[NEW_GAME].press(mouseCoord))
		{
			if (isFolderSelected)
			{
				PreSettings preSettings1(saveFolderName);
				startNewGame = true;
				return PRE_SETTINGS_MENU;
			}
			else
			{
				isTextVisible = true;
			}
		}

		if (buttons[EXIT_TO_MENU].press(mouseCoord))
			return MAIN_MENU;

		t1::system::sleep(16);
	}

	return CHOISE_FOLDER_MENU;
}



void ChoiseFolderMenu::relocate(const sf::Vector2u windowSize)
{
	SubWindow::relocateCentral(windowSize);
	for (auto& btn : buttons)
	{
		btn.relocate(position);
	}

	helpText.setPosition(position.x + 70, position.y + 350);
}



void ChoiseFolderMenu::draw(sf::RenderWindow& window)
{
	if (isVisible)
	{
		this->drawSubWindowBase(window);
		for (auto& btn : buttons)
		{
			btn.draw(window);
		}

		if (isTextVisible)
			window.draw(helpText);
	}
}
