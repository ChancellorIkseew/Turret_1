
#include <thread>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "menu.h"

#include "game_interface/main_window/main_window_resize.h"
#include "game_interface/main_window/main_window.h"
#include "game_interface/ui_window/sub_win_types/text_field/text_field.h"

#include "t1_system/input/input_handler.h"
#include "t1_system/sleep.h"

#include "ui_elements/main_menu.h"
#include "ui_elements/choise_save_folder.h"
#include "ui_elements/pre_settings.h"
#include "t1_system/t1_mutex.h"


GameState openMenu(sf::RenderWindow& mainWindow, bool& startNewGame, std::string& saveFolderName, PreSettings& preSettings)
{
	sf::Image backImage;
	backImage.loadFromFile("images/background.bmp");
	sf::Texture backTexture;
	backTexture.loadFromImage(backImage);
	sf::Sprite backSprite;
	backSprite.setTexture(backTexture);
    backSprite.setPosition(-100, -100);
	
	sf::Vector2i mouseCoord;
	
	MainMenu mainMenu;
	ChoiseFolderMenu choiseFolderMenu;
	PreSettingsWindow preSettingsWindow;
	
	bool isMenuOpen = true;
	bool exit = false;

	std::thread input([&]()
		{
			GameState menuTab = GameState::MAIN_MENU;

			while (isMenuOpen)
			{
				if (menuTab == GameState::MAIN_MENU)
				{
					mainMenu.setVisible(true);
					menuTab = mainMenu.interact(isMenuOpen);
					mainMenu.setVisible(false);
				}
				
				if (menuTab == GameState::CHOISE_FOLDER_MENU)
				{
					choiseFolderMenu.setVisible(true);
					menuTab = choiseFolderMenu.interact(isMenuOpen, startNewGame, saveFolderName);
					choiseFolderMenu.setVisible(false);
				}

				if (menuTab == GameState::PRE_SETTINGS_MENU)
				{
					preSettingsWindow.setVisible(true);
					menuTab = preSettingsWindow.interact(isMenuOpen, preSettings);
					preSettingsWindow.setVisible(false);
				}

				if (menuTab == GameState::GAMEPLAY)
				{
					isMenuOpen = false;
					exit = false;
				}

				if (menuTab == GameState::EXIT)
				{
					isMenuOpen = false;
					exit = true;
				}

				t1::system::sleep(16);
			}
		}
	);

	sf::Event event;
	while (isMenuOpen)
    {
		mouseCoord = sf::Mouse::getPosition(mainWindow);
        
        while (mainWindow.pollEvent(event))
        {
			InputHandler::updateInput(event);
			InputHandler::updateMouseCoord(mainWindow);
			
			if (event.type == sf::Event::Closed)
			{
				mainWindow.close();
				isMenuOpen = false;
				exit = true;
			}

			if (event.type == sf::Event::Resized || UIWindow::windowCreated)
			{
				UIWindow::windowCreated = false;
				overlayResize(mainWindow);
				mainMenu.relocate(mainWindow.getSize());
				choiseFolderMenu.relocate(mainWindow.getSize());
				preSettingsWindow.relocate(mainWindow.getSize());
			}
		}

		mainWindow.clear(sf::Color::Black);
		
		mainWindow.draw(backSprite);
		
		mainMenu.draw(mainWindow);
		choiseFolderMenu.draw(mainWindow);
		preSettingsWindow.draw(mainWindow);

		mainWindow.display();
	}
	
	input.join();
	
	if (!exit)
	{
		return GameState::GAMEPLAY;
	}
	return GameState::EXIT;
}
