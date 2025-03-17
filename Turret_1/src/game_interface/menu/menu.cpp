
#include <thread>

#include "menu.h"

#include "game_interface/main_window/main_window_resize.h"
#include "game_interface/main_window/main_window.h"
#include "game_interface/ui_window/sub_win_types/text_field/text_field.h"

#include "t1_system/input/input_handler.h"
#include "t1_system/sleep.h"

#include "ui_elements/main_menu.h"
#include "ui_elements/choise_save_folder.h"
#include "ui_elements/pre_settings.h"
#include "game_interface/gameplay/ui_elements/settings_window.h"
#include "t1_system/t1_mutex.h"


GameState openMenu(sf::RenderWindow& mainWindow, bool& startNewGame, std::string& saveFolderName, PreSettings& preSettings)
{
	sf::Image backImage;
	backImage.loadFromFile("images/background.bmp");
	sf::Texture backTexture;
	backTexture.loadFromImage(backImage);
	sf::Sprite backSprite(backTexture);
	backSprite.setPosition({ -100, -100 });
	
	MainMenu mainMenu;
	ChoiseFolderMenu choiseFolderMenu;
	PreSettingsWindow preSettingsWindow;
	SettingsWindow settingsWindow;
	
	bool isMenuOpen = true;
	bool exit = false;

	std::thread input([&]()
		{
			GameState menuTab = GameState::MAIN_MENU;

			while (isMenuOpen)
			{
				switch (menuTab)
				{
				case GameState::MAIN_MENU:
					mainMenu.setVisible(true);
					menuTab = mainMenu.interact(isMenuOpen);
					mainMenu.setVisible(false);
					break;
				case GameState::CHOISE_FOLDER_MENU:
					choiseFolderMenu.setVisible(true);
					menuTab = choiseFolderMenu.interact(isMenuOpen, startNewGame, saveFolderName);
					choiseFolderMenu.setVisible(false);
					break;
				case GameState::PRE_SETTINGS_MENU:
					preSettingsWindow.setVisible(true);
					menuTab = preSettingsWindow.interact(isMenuOpen, preSettings);
					preSettingsWindow.setVisible(false);
					break;
				case GameState::OPTIONS:
					settingsWindow.setVisible(true);
					settingsWindow.interact(isMenuOpen);
					settingsWindow.setVisible(false);
					menuTab = GameState::MAIN_MENU;
					break;
				case GameState::EXIT:
					exit = true;
					[[fallthrough]];
				case GameState::GAMEPLAY:
					isMenuOpen = false;
					break;
				}
				t1::system::sleep(16);
			}
		}
	);

	while (isMenuOpen)
    {
        while (const std::optional event = mainWindow.pollEvent())
        {
			InputHandler::updateInput(event);
			InputHandler::updateMouseCoord(mainWindow);
			
			if (event->is<sf::Event::Closed>())
			{
				mainWindow.close();
				isMenuOpen = false;
				exit = true;
			}

			if (event->is<sf::Event::Resized>() || UIWindow::windowCreated)
			{
				UIWindow::windowCreated = false;
				overlayResize(mainWindow);
				sf::Vector2i mainWindowSize = sf::Vector2i(mainWindow.getSize());
				mainMenu.relocate(mainWindowSize);
				choiseFolderMenu.relocate(mainWindowSize);
				preSettingsWindow.relocate(mainWindowSize);
				settingsWindow.relocate(mainWindowSize);
			}
		}

		mainWindow.clear(sf::Color::Black);
		
		mainWindow.draw(backSprite);
		
		mainMenu.draw(mainWindow);
		choiseFolderMenu.draw(mainWindow);
		preSettingsWindow.draw(mainWindow);
		settingsWindow.draw(mainWindow);

		mainWindow.display();
	}
	
	input.join();
	
	if (exit)
		return GameState::EXIT;
	return GameState::GAMEPLAY;
}
