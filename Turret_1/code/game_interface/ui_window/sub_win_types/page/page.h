#pragma once
#ifndef T1_GUI_PAGE_H
#define T1_GUI_PAGE_H

#include <any>
#include <SFML/Graphics.hpp>
#include "game_interface/ui_window/ui_window/ui_plate.h"

class PreSettings;

class Page : public UIPlate
{
private:
	sf::Vector2u ownerPosition;

public:
	Page(const sf::Vector2u size, const sf::Vector2u position);
	virtual ~Page() = default;

	virtual void interact() = 0;
	virtual void enter(PreSettings& preSettings) = 0;
	virtual void relocateWithOwner(const sf::Vector2u ownerPosition);

};

#endif // T1_GUI_PAGE_H
