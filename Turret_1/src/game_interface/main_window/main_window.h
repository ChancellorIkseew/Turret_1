#pragma once
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <SFML/Graphics.hpp>

class MainWindow
{
private:
	static sf::View overlay;

public:
	static void open();
	static void startMenuCycle(sf::RenderWindow& mainWindow);
	static void resize(sf::RenderWindow& mainWindow);

	static const sf::View& getOverlay() { return overlay; }
};

#endif // MAIN_WINDOW_H
