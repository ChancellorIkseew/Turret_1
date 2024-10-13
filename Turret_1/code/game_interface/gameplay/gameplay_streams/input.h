#pragma once
#ifndef T1_GAMEPL_INPUT_H
#define T1_GAMEPL_INPUT_H

#include <SFML/Graphics.hpp>

class Team;

namespace t1::gamepl
{
    void input(bool& isGameplayActive, bool& isPaused, sf::RenderWindow& mainWindow,
        sf::Vector2i& mouseCoord, sf::Vector2f& mouseMapCoord, sf::Vector2f& lastMousePosition,
        bool& isMovingCamera, const std::string& saveFolderName, Team* team);
}

#endif // T1_GAMEPL_INPUT_H
