
#include <SFML/Graphics.hpp>

#include "ui_window.h"




UIWindow::UIWindow(const sf::Vector2i size, const sf::Vector2i position) : UIPlate(size, position) {
	windowCreated = true; // static field
}
UIWindow::UIWindow(const sf::Vector2i size) : UIPlate(size) {
	windowCreated = true; // static field
}

void UIWindow::relocateCentral(const sf::Vector2i windowSize) {
	position = (windowSize - size) / 2;
}
void UIWindow::relocate(const sf::Vector2i windowSize) { }
