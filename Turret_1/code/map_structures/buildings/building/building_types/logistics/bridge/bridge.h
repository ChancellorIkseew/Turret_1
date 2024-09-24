#pragma once
#ifndef BRIDGE_H
#define BRIDGE_H

#include "SFML/Graphics.hpp"

#include "map_structures/buildings/building/building.h"


class Bridge : public Building
{
private:

	char direction;

public:

	Bridge(int type, char direction, short durability, short size, const TileCoord tile);
	~Bridge() = default;

	void save(std::ofstream& fout) const override;
	void load(std::ifstream& fin) override;

	void interact() override;
	void transmitResourceUnit();

	bool canAccept(int resType) const override;
	bool isThisPositionFree(int position) const override;

	void draw(sf::RenderWindow& window) override;

};

#endif // BRIDGE_H
