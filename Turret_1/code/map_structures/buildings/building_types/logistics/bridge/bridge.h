#pragma once
#ifndef BRIDGE_H
#define BRIDGE_H

#include "SFML/Graphics.hpp"

#include "map_structures/buildings/building/building.h"


class Bridge : public Building
{
public:

	Bridge(int type, char direction, short durability, short size, const TileCoord tile);
	~Bridge() = default;

	void save(std::ofstream& fout) const override final;
	void load(std::ifstream& fin) override final;

	void interact() override final;
	void transmitResourceUnit();

	bool canAccept(int resType) const override final;
	bool isThisPositionFree(int position) const override final;

	void draw(sf::RenderWindow& window) override final;

};

#endif // BRIDGE_H
