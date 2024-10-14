#pragma once
#ifndef SUB_WINDOWS_LIST
#define SUB_WINDOWS_LIST

#include <SFML/Graphics.hpp>
#include <list>

#include "sub_window.h"


extern std::list<SubWindow*> SubWindowsList;

void initSubWindows();

void relocateSubWindows(const sf::Vector2u);

bool noSubWindowSelected(sf::Vector2i mouseCoord);


#endif // SUB_WINDOWS_LIST
