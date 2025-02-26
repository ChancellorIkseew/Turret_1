#pragma once
#ifndef  MAIN_WINDOW_RESIZE_H
#define MAIN_WINDOW_RESIZE_H

#include <SFML/Graphics.hpp>

inline sf::View overlay;

void mainWindowResize(sf::RenderWindow& mainWindow);
void overlayResize(sf::RenderWindow& mainWindow);

#endif // MAIN_WINDOW_RESIZE_H
