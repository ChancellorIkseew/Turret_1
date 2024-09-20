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

	Bridge(int v_type, char v_direction, short v_durability, short v_size, int tileX, int tileY);
	Bridge();
	~Bridge() = default;

	void save(std::ofstream& fout) override;
	void load(std::ifstream& fin) override;

	void interact() override;
	void transmitResourceUnit();

	bool canAccept(int resType) override;
	bool isThisPositionFree(int position) override;

	void draw(sf::RenderWindow& window) override;

};


#endif // BRIDGE_H
