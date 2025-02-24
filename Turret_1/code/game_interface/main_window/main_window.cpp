
#include "main_window.h"
#include "main_window_resize.h"
#include "game_state.h"

#include "game_interface/menu/menu.h"
#include "game_interface/gameplay/gameplay.h"

#include "game_interface/ui_window/ui_window/ui_plate.h"
#include "game_interface/sound_system/sound_system.h"
#include "game_interface/settings/settings.h"


void openMainWindow()
{
	Settings::load();

	GameSound g1; // Test music implrmrntation. Will be expanded and reimplemented.
	g1.loadSound();
	g1.start();

	UIPlate::init();

	sf::RenderWindow mainWindow(sf::VideoMode(800, 600), L"Турельница. Версия альфа_0.6.4", sf::Style::Default);
	mainWindow.setFramerateLimit(60);
	overlay.setSize(sf::Vector2f(800.0f, 600.0f));

	startMenuCycle(mainWindow);
}


void startMenuCycle(sf::RenderWindow& mainWindow)
{
	PreSettings preSettings;
	std::string saveFolderName = "0";
	bool startNewGame = false;
	GameState newGameState = GameState::MAIN_MENU;

	while (mainWindow.isOpen())
	{
		if (newGameState == GameState::MAIN_MENU)
			newGameState = openMenu(mainWindow, startNewGame, saveFolderName, preSettings);

		if (newGameState == GameState::GAMEPLAY)
		{
			Gameplay gameplay;
			newGameState = gameplay.startGameplay(mainWindow, startNewGame, saveFolderName, preSettings);
		}

		if (newGameState == GameState::EXIT)
			mainWindow.close();
	}
}