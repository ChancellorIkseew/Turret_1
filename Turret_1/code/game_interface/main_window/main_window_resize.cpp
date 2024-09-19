
#include <iostream>
#include <SFML/Graphics.hpp>

#include "main_window_resize.h"

#include "game_interface/settings/settings_util/settings_save_system.h"
#include "game_interface/gameplay/sub_windows/sub_windows_util/sub_windows_list.h"


sf::View overlay;

int overlaySizeX = 800;
int overlaySizeY = 600;

int oldWinSizeX = 0;
int oldWinSizeY = 0;

void overlayResize(sf::RenderWindow& mainWindow)
{
	if (mainWindow.getSize().x != oldWinSizeX || mainWindow.getSize().y != oldWinSizeY)
	{
		mainWindowResize(mainWindow);

		std::cout << "resize_works_2" << '\n';
		overlaySizeX = mainWindow.getSize().x;
		overlaySizeY = mainWindow.getSize().y;

		oldWinSizeX = mainWindow.getSize().x;
		oldWinSizeY = mainWindow.getSize().y;

		//std::cout << overlaySizeX << " " << overlaySizeY << '\n';

		overlay.setSize(sf::Vector2f(overlaySizeX, overlaySizeY));
		overlay.setCenter(sf::Vector2f(overlaySizeX / 2, overlaySizeY / 2));

		mainWindow.setView(overlay);

		relocateSubWindows(mainWindow.getSize().x, mainWindow.getSize().y);
	}
	
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
