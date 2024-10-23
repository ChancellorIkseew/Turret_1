#pragma once
#ifndef BRIDGE_H
#define BRIDGE_H

#include "SFML/Graphics.hpp"

#include "map_structures/buildings/building/building.h"


class Bridge : public Building
{
public:
	Bridge(const uint16_t type, const char direction, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team);
	~Bridge() = default;

	void save(std::ofstream& fout) const override final;
	void load(std::ifstream& fin) override final;

	void interact() override final;
	void transmitResourceUnit();
	bool canAccept(const uint16_t resType) const override final;

	void draw(sf::RenderWindow& window) override final;

};

#endif // BRIDGE_H
