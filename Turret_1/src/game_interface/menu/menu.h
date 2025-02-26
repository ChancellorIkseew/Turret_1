#pragma once
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "map_structures/pre-settings/pre-settings.h"

enum class GameState;

GameState openMenu(sf::RenderWindow& mainWindow, bool& startNewGame, std::string& saveFolderName, PreSettings& preSettings);


#endif // MENU_H
