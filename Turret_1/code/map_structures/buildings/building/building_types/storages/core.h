#pragma once
#ifndef CORE_H
#define CORE_H

#include "SFML/Graphics.hpp"

#include "map_structures/buildings/buildings_map.h"


class Core : public Building
{
protected:

public:

	Core(int type, short durability, short size, int tileX, int tileY);
	Core();
	virtual ~Core() = default;

	void interact() override;

	bool canAccept(int resType) override;
	bool isThisPositionFree(int position) override;

	virtual void draw(sf::RenderWindow& window) override;
	
};


#endif // CORE_H
