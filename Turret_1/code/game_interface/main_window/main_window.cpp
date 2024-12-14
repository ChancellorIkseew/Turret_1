
#include "main_window.h"
#include "main_window_resize.h"

#include "game_interface/menu/menu.h"
#include "game_interface/gameplay/gameplay.h"

#include "game_interface/ui_window/ui_window/ui_plate.h"
#include "game_interface/sound_system/sound_system.h"
#include "game_interface/settings/settings_util/settings_save_system.h"


void openMainWindow()
{
	loadSettings();

	GameSound g1;

	g1.loadSound();
	g1.start();

	UIPlate::init();

	sf::RenderWindow mainWindow(sf::VideoMode(800, 600), L"Турельница. Версия альфа_0.6.1", sf::Style::Default);
	mainWindow.setFramerateLimit(60);
	overlay.setSize(sf::Vector2f(800.0f, 600.0f));

	std::string saveFolderName = "0";
	bool startNewGame = false;

	char currentFunction = MAIN_MENU;
	
	while (mainWindow.isOpen())
	{
		if (currentFunction == MAIN_MENU)
			currentFunction = openMenu(mainWindow, startNewGame, saveFolderName);
		
		if (currentFunction == GAMEPLAY)
		{
			Gameplay gameplay;
			currentFunction = gameplay.startGameplay(mainWindow, startNewGame, saveFolderName);
		}

		if (currentFunction == EXIT)
			mainWindow.close();
	}

	return;
}