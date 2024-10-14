#pragma once
#ifndef T1_GUI_PAGE_H
#define T1_GUI_PAGE_H

#include <SFML/Graphics.hpp>
#include "game_interface/gameplay/sub_windows/sub_windows_util/sub_window.h"


class Page : public SubWindow
{
public:
	Page(const sf::Vector2u size, const sf::Vector2u position);
	~Page() = default;

	virtual void interact(const sf::Vector2i& mouseCoord, bool& isMenuOpen) = 0;
	virtual void relocate(const sf::Vector2u ownerPosition);

};

#endif // T1_GUI_PAGE_H
