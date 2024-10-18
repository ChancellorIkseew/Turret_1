
#include <SFML/Graphics.hpp>

#include "ui_window.h"




UIWindow::UIWindow(const sf::Vector2u size, const sf::Vector2u position) : UIPlate(size, position)
{
	windowCreated = true;
}


void UIWindow::relocateCentral(const sf::Vector2u windowSize)
{
	position = sf::Vector2u((windowSize.x - size.x) / 2, (windowSize.y - size.y) / 2);
}

void UIWindow::relocate(const sf::Vector2u windowSize) { }
