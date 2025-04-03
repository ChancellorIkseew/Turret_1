
#include <iostream>
#include <SFML/Graphics.hpp>

#include "main_window.h"

#include "game_interface/settings/settings.h"


static inline void checkSize(sf::RenderWindow& mainWindow)
{
	const sf::Vector2u maxSize = Settings::getDisplay().windowMaxSize;
	if (mainWindow.getSize().x > maxSize.x)
		mainWindow.setSize(sf::Vector2u(maxSize.x, mainWindow.getSize().y));
	if (mainWindow.getSize().y > maxSize.y)
		mainWindow.setSize(sf::Vector2u(mainWindow.getSize().x, maxSize.y));
}

void MainWindow::resize(sf::RenderWindow& mainWindow)
{
	checkSize(mainWindow);
	sf::Vector2f size = sf::Vector2f(mainWindow.getSize());
	std::cout << size.x << " " << size.y << '\n';
	overlay.setSize(size);
	overlay.setCenter(size / 2.0f);
	mainWindow.setView(overlay);
}
