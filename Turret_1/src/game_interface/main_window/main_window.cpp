
#include "main_window.h"
#include "main_window_resize.h"
#include "game_state.h"

#include "game_interface/menu/menu.h"
#include "game_interface/gameplay/gameplay.h"

#include "game_interface/ui_window/ui_window/ui_plate.h"
#include "game_interface/sound_system/sound_system.h"


void openMainWindow()
{
	SoundSystem::loadSounds();
	SoundSystem::startMusic();

	UIPlate::init();

	sf::RenderWindow mainWindow(sf::VideoMode(sf::Vector2u(800, 600), 32), L"����������. ������ �����_0.7.0", sf::Style::Default);
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