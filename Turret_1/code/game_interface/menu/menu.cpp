
#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>

#include "../main_window/main_window_resize.h"
#include "../main_window/main_window.h"

#include "../system/system.h"

#include "sub_windows/main_menu.h"
#include "sub_windows/choise_save_folder.h"
#include "sub_windows/pre_settings.h"


char openMenu(sf::RenderWindow& mainWindow, bool& startNewGame, std::string& saveFolderName)
{
	oldWinSizeX = 0;
	overlayResize(mainWindow);

	sf::Image backImage;									//Terrain
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
			int menuTab = MAIN_MENU;

			while (isMenuOpen)
			{
				if (menuTab == MAIN_MENU)
				{
					mainMenu.setVisible(true);
					menuTab = mainMenu.interact(mouseCoord, isMenuOpen);
					mainMenu.setVisible(false);
				}
				
				if (menuTab == CHOISE_FOLDER_MENU)
				{
					choiseFolderMenu.setVisible(true);
					menuTab = choiseFolderMenu.interact(mouseCoord, isMenuOpen, startNewGame, saveFolderName);
					choiseFolderMenu.setVisible(false);
				}

				if (menuTab == PRE_SETTINGS_MENU)
				{
					preSettingsWindow.setVisible(true);
					menuTab = preSettingsWindow.interact(mouseCoord, isMenuOpen);
					preSettingsWindow.setVisible(false);
				}

				if (menuTab == GAMEPLAY)
				{
					isMenuOpen = false;
					exit = false;
				}

				if (menuTab == EXIT)
				{
					isMenuOpen = false;
					exit = true;
				}

				Sleep(16);
			}
		}
	);

	while (isMenuOpen)
    {
		mouseCoord = sf::Mouse::getPosition(mainWindow);

        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
			if (event.type == sf::Event::Closed)
			{
				mainWindow.close();
				isMenuOpen = false;
				exit = true;
			}

			if (event.type = sf::Event::Resized)
			{
				//std::cout << "resize_works_0" << '\n';
				overlayResize(mainWindow);
				mainMenu.relocate(mainWindow.getSize().x, mainWindow.getSize().y);
				choiseFolderMenu.relocate(mainWindow.getSize().x, mainWindow.getSize().y);
				preSettingsWindow.relocate(mainWindow.getSize().x, mainWindow.getSize().y);
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
		return GAMEPLAY;
	}
	return EXIT;
}