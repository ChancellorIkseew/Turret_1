#pragma once
#ifndef CORE_H
#define CORE_H

#include "SFML/Graphics.hpp"
#include "map_structures/buildings/building/building.h"


class Core : public Building
{
protected:

public:

	Core(int type, short durability, short size, const TileCoord tile, Team* team);
	virtual ~Core() = default;

	void interact() override;
	bool canAccept(const uint16_t resType) const override;

	virtual void draw(sf::RenderWindow& window) override;
	
};

#endif // CORE_H
