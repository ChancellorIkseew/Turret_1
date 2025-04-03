
#include "main_window.h"
#include "game_state.h"

#include "game_interface/menu/menu.h"
#include "game_interface/gameplay/gameplay.h"
#include "game_interface/settings/settings.h"

#include "game_interface/sound_system/sound_system.h"

sf::View MainWindow::overlay;

void MainWindow::open()
{
	SoundSystem::loadSounds();
	SoundSystem::startMusic();

	sf::Vector2u resolution = Settings::getDisplay().windowMaxSize;
	sf::State state = Settings::getDisplay().fullscreen ? sf::State::Fullscreen : sf::State::Windowed;
	sf::RenderWindow mainWindow(sf::VideoMode(resolution, 32), L"Турельница. Версия альфа_0.7.0", state);
	mainWindow.setFramerateLimit(60);
	mainWindow.setVerticalSyncEnabled(state == sf::State::Fullscreen);
	sf::Image icon;
	if (icon.loadFromFile("images/icon.bmp"))
		mainWindow.setIcon(sf::Vector2u(32, 32), icon.getPixelsPtr());
	overlay.setSize(sf::Vector2f(800.0f, 600.0f));

	startMenuCycle(mainWindow);
}


void MainWindow::startMenuCycle(sf::RenderWindow& mainWindow)
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