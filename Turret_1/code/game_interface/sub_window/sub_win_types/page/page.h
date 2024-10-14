#pragma once
#ifndef T1_GUI_PAGE_H
#define T1_GUI_PAGE_H

#include <SFML/Graphics.hpp>
#include "game_interface/sub_window/sub_window/sub_window.h"


class Page : public SubWindow
{
private:
	sf::Vector2u ownerPosition;

public:
	Page(const sf::Vector2u size, const sf::Vector2u position);
	~Page() = default;

	virtual void interact(const sf::Vector2i& mouseCoord, bool& isMenuOpen) = 0;
	virtual void enter();
	virtual void relocate(const sf::Vector2u ownerPosition);

};

#endif // T1_GUI_PAGE_H
