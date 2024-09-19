#pragma once
#ifndef  MAIN_WINDOW_RESIZE_H
#define MAIN_WINDOW_RESIZE_H

#include <SFML/Graphics.hpp>

extern sf::View overlay;

extern int overlaySizeX;
extern int overlaySizeY;

extern int oldWinSizeX;
extern int oldWinSizeY;

void mainWindowResize(sf::RenderWindow& mainWindow);

void overlayResize(sf::RenderWindow& mainWindow);


#endif // MAIN_WINDOW_RESIZE_H
