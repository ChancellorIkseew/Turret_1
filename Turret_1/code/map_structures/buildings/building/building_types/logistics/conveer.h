#pragma once
#ifndef CONVEYER_H
#define CONVEYER_H

#include "map_structures/buildings/buildings_map.h"
#include "SFML/Graphics.hpp"


class Conveyer : public Building
{
private:

	char direction;

	bool isPositionFree[5];

public:

	Conveyer(char type, char direction, short durability, short v_size, int tileX, int tileY);
	Conveyer();
	virtual ~Conveyer() = default;

	void save(std::ofstream& fout) const override;
	virtual void load(std::ifstream& fin) override;

	bool canAccept(int resType) const override;
	bool isThisPositionFree(int position) const override;
	void leavePosition(int position) override;
	void takePosition(int position) override;

	virtual void draw(sf::RenderWindow& window) override;
	
};


#endif // CONVEYER_H
