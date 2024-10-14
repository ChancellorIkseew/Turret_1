
#include <iostream>

#include "main_window.h"

#include "main_window_resize.h"

#include "game_interface/menu/menu.h"
#include "game_interface/gameplay/gameplay.h"

#include "game_interface/sub_window/sub_window/sub_window.h"
#include "game_interface/sub_window/sub_win_util/sub_windows_list.h"
#include "game_interface/sub_window/sub_win_util/fonts.h"

#include "game_interface/sound_system/sound_system.h"

#include "game_interface/settings/settings_util/settings_save_system.h"


void openMainWindow()
{
	GameSound g1;

	g1.loadSound();
	g1.start();

	SubWindow::init();
	//initFonts();


	sf::RenderWindow mainWindow(sf::VideoMode(800, 600), L"Турельница. Версия альфа_0.5.6", sf::Style::Default);

	mainWindow.setFramerateLimit(60);
	
	
	overlay.setSize(sf::Vector2f(800, 600));
	overlay.setCenter(sf::Vector2f(400, 300));

	loadSettings();

	std::string saveFolderName = "0";
	bool startNewGame = false;

	char currentFunction = MAIN_MENU;
	
	while (mainWindow.isOpen())
	{
		if (currentFunction == MAIN_MENU)
			currentFunction = openMenu(mainWindow, startNewGame, saveFolderName);
		
		if (currentFunction == GAMEPLAY)
			currentFunction = t1::gamepl::startGameplay(mainWindow, startNewGame, saveFolderName);

		if (currentFunction == EXIT)
			mainWindow.close();
	}

	return;
}