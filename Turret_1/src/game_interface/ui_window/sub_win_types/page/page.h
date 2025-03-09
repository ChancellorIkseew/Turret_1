#pragma once
#ifndef T1_GUI_PAGE_H
#define T1_GUI_PAGE_H

#include <SFML/Graphics.hpp>
#include "game_interface/ui_window/ui_window/ui_plate.h"

class PreSettings;

class Page : public UIPlate
{
private:
	sf::Vector2i ownerPosition;

public:
	Page(const sf::Vector2i size, const sf::Vector2i position);
	virtual ~Page() = default;

	virtual void interact() = 0;
	virtual void enter(PreSettings& preSettings) = 0;
	virtual void relocateWithOwner(const sf::Vector2i ownerPosition);

};

#endif // T1_GUI_PAGE_H
