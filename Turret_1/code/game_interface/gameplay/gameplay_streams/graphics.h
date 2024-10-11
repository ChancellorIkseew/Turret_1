#pragma once
#ifndef T1_GRAPHICS_THREAD_H
#define T1_GRAPHICS_THREAD_H

#include <SFML/Graphics.hpp>

namespace t1::gamepl
{
	void graphics(bool& isGameplayActive, const bool& isPaused, sf::RenderWindow& mainWindow,
        sf::Vector2i& mouseCoord, sf::Vector2f& mouseMapCoord, sf::Vector2f& lastMousePosition,
        bool& isMovingCamera);
}

#endif // T1_GRAPHICS_THREAD_H
