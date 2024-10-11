#pragma once
#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <SFML/Graphics.hpp>

namespace t1::gamepl
{
	char startGameplay(sf::RenderWindow& mainWindow, bool startNewGame, std::string saveFolderName);
};

#endif // GAMEPLAY_H
