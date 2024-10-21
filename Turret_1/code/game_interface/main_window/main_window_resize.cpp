
#include <iostream>
#include <SFML/Graphics.hpp>

#include "main_window_resize.h"

#include "game_interface/settings/settings_util/settings_save_system.h"
#include "game_interface/ui_window/sub_win_util/ui_windows_list.h"


void overlayResize(sf::RenderWindow& mainWindow)
{
	std::cout << "resize_works_1" << '\n';
	mainWindowResize(mainWindow);

	sf::Vector2u overlaySize = mainWindow.getSize();

	std::cout << overlaySize.x << " " << overlaySize.y << '\n';

	overlay.setSize(sf::Vector2f(overlaySize.x, overlaySize.y));
	overlay.setCenter(sf::Vector2f(overlaySize.x / 2, overlaySize.y / 2));

	mainWindow.setView(overlay);

	relocateSubWindows(mainWindow.getSize());
}
		


void mainWindowResize(sf::RenderWindow& mainWindow)
{
	if (mainWindow.getSize().x > maxGameplayWindowSizeX)	// mainWindow_scaling block
	{
		std::cout << "mainWindow size chek works" << '\n';

		mainWindow.setSize(sf::Vector2u(maxGameplayWindowSizeX, mainWindow.getSize().y));
	}

	if (mainWindow.getSize().y > maxGameplayWindowSizeY)
	{
		std::cout << "mainWindow size chek works" << '\n';

		mainWindow.setSize(sf::Vector2u(mainWindow.getSize().x, maxGameplayWindowSizeY));
	}

}
