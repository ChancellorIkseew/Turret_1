#pragma once
#ifndef CONVEYER_H
#define CONVEYER_H

#include "map_structures/buildings/building/building.h"
#include "SFML/Graphics.hpp"


class Conveyer : public Building
{
protected:
	bool isPositionFree[5];

public:

	Conveyer(char type, char direction, short durability, short v_size, const TileCoord tile);
	virtual ~Conveyer() = default;

	void save(std::ofstream& fout) const override final;
	virtual void load(std::ifstream& fin) override final;

	bool canAccept(int resType) const override final;
	bool isThisPositionFree(int position) const override final;
	void leavePosition(int position) override final;
	void takePosition(int position) override final;

	virtual void draw(sf::RenderWindow& window) override;
	
};

#endif // CONVEYER_H
