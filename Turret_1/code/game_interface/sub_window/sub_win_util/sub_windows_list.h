#pragma once
#ifndef SUB_WINDOWS_LIST
#define SUB_WINDOWS_LIST

#include <SFML/Graphics.hpp>


void initSubWindows();

void relocateSubWindows(const sf::Vector2u);

bool noSubWindowSelected(sf::Vector2i mouseCoord);


#endif // SUB_WINDOWS_LIST
