
#include <iostream>
#include <SFML/Graphics.hpp>

#include "main_window.h"

#include "main_window_resize.h"

#include "../menu/menu.h"
#include "../gameplay/gameplay.h"

#include "../gameplay/sub_windows/sub_windows_util/sub_window.h"
#include "../gameplay/sub_windows/sub_windows_util/sub_windows_list.h"
#include "../gameplay/sub_windows/sub_windows_util/fonts.h"

#include "../sound_system/sound_system.h"

#include "../settings/settings_util/settings_save_system.h"


void openMainWindow()
{
	GameSound g1;

	g1.loadSound();
	g1.start();

	SubWindow::init();
	//initFonts();


	sf::RenderWindow mainWindow(sf::VideoMode(800, 600), L"����������. ������ �����_0.5.2", sf::Style::Default);

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
			currentFunction = startGameplay(mainWindow, startNewGame, saveFolderName);

		//if (currentFunction == EXIT)
			
	}

	//mainWindow.close();
	return;
}