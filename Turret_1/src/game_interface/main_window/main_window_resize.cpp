
#include <iostream>
#include <SFML/Graphics.hpp>

#include "main_window_resize.h"

#include "game_interface/settings/settings.h"


void overlayResize(sf::RenderWindow& mainWindow)
{
	mainWindowResize(mainWindow);
	sf::Vector2u overlaySize = mainWindow.getSize();
	std::cout << overlaySize.x << " " << overlaySize.y << '\n';
	overlay.setSize(sf::Vector2f(overlaySize));
	overlay.setCenter(sf::Vector2f(overlaySize.x / 2, overlaySize.y / 2));
	mainWindow.setView(overlay);
}

void mainWindowResize(sf::RenderWindow& mainWindow)
{
	if (mainWindow.getSize().x > Settings::getDisplay().windowMaxSize.x)
		mainWindow.setSize(sf::Vector2u(Settings::getDisplay().windowMaxSize.x, mainWindow.getSize().y));
	if (mainWindow.getSize().y > Settings::Settings::getDisplay().windowMaxSize.y)
		mainWindow.setSize(sf::Vector2u(mainWindow.getSize().x, Settings::getDisplay().windowMaxSize.y));
}
