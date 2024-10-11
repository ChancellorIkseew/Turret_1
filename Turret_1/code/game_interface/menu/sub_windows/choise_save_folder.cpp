
#include <iostream>
#include <SFML/Graphics.hpp>

#include "choise_save_folder.h"

#include "game_interface/gameplay/sub_windows/sub_windows_util/fonts.h"
#include "game_interface/system/sleep.h"
#include "game_interface/main_window/main_window.h"

#include "map_structures/pre-settings/pre-settings.h"

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


ChoiseFolderMenu::ChoiseFolderMenu() : SubWindow('s', 720, 480, 100, 100)
{
	isFolderSelected = false;
	isTextVisible = false;
	this->prepareInterfaceSprites();
	this->relocate(1920, 1080);
	isVisible = false;
}



void ChoiseFolderMenu::prepareInterfaceSprites()
{
	newGame = Button("new_game.bmp", sf::Vector2i(242, 48), sf::Vector2i(10, 100));
	loadGame = Button("load_game.bmp", sf::Vector2i(364, 48), sf::Vector2i(10, 170));
	exitToMenu = Button("exit_to_menu.bmp", sf::Vector2i(48, 48), sf::Vector2i(10, 10));

	load1 = Button("choise_load.bmp", sf::Vector2i(48, 48), sf::Vector2i(10, 240));
	load2 = Button("choise_load.bmp", sf::Vector2i(48, 48), sf::Vector2i(70, 240));
	load3 = Button("choise_load.bmp", sf::Vector2i(48, 48), sf::Vector2i(130, 240));
	load4 = Button("choise_load.bmp", sf::Vector2i(48, 48), sf::Vector2i(190, 240));
	load5 = Button("choise_load.bmp", sf::Vector2i(48, 48), sf::Vector2i(250, 240));

	helpText.setFont(turretClassic);
	helpText.setString(sf::String(L"„тобы начать игру, нужно выбрать сохранение,\nв которое будет записыватьс€ игровой прогресс."));
	helpText.setCharacterSize(16);
	helpText.setFillColor(sf::Color(68, 52, 52));
}



int ChoiseFolderMenu::interact(sf::Vector2i& mouseCoord, bool& isMenuOpen, bool& startNewGame, std::string& saveFolderName)
{
	while (isMenuOpen)
	{
		if (load1.press(mouseCoord))
		{
			saveFolderName = selectFolder("save1", isFolderSelected);
			isTextVisible = false;
		}

		if (load2.press(mouseCoord))
		{
			saveFolderName = selectFolder("save2", isFolderSelected);
			isTextVisible = false;
		}

		if (load3.press(mouseCoord))
		{
			saveFolderName = selectFolder("save3", isFolderSelected);
			isTextVisible = false;
		}

		if (load4.press(mouseCoord))
		{
			saveFolderName = selectFolder("save4", isFolderSelected);
			isTextVisible = false;
		}

		if (load5.press(mouseCoord))
		{
			saveFolderName = selectFolder("save5", isFolderSelected);
			isTextVisible = false;
		}


		if (loadGame.press(mouseCoord))
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

		if (newGame.press(mouseCoord))
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

		if (exitToMenu.press(mouseCoord))
			return MAIN_MENU;

		t1::system::sleep(16);
	}

	return CHOISE_FOLDER_MENU;
}



void ChoiseFolderMenu::relocate(int windowSizeX, int windowSizeY)
{
	positionX = (windowSizeX - sizeX) / 2;
	positionY = (windowSizeY - sizeY) / 2;

	newGame.relocate(sf::Vector2i(positionX, positionY));
	loadGame.relocate(sf::Vector2i(positionX, positionY));
	exitToMenu.relocate(sf::Vector2i(positionX, positionY));

	load1.relocate(sf::Vector2i(positionX, positionY));
	load2.relocate(sf::Vector2i(positionX, positionY));
	load3.relocate(sf::Vector2i(positionX, positionY));
	load4.relocate(sf::Vector2i(positionX, positionY));
	load5.relocate(sf::Vector2i(positionX, positionY));

	helpText.setPosition(positionX + 70, positionY + 350);
}



void ChoiseFolderMenu::draw(sf::RenderWindow& window)
{
	if (isVisible)
	{
		this->drawSubWindowBase(window);
		if (isTextVisible)
		{
			window.draw(helpText);
		}

		newGame.draw(window);
		loadGame.draw(window);
		exitToMenu.draw(window);

		load1.draw(window);
		load2.draw(window);
		load3.draw(window);
		load4.draw(window);
		load5.draw(window);
	}
}
