#pragma once
#ifndef SHIELDED_CONVEYER_H
#define SHIELDED_CONVEYER_H

#include "SFML/Graphics.hpp"

#include "map_structures/buildings/building/building_types/logistics/conveer.h"


class ShieldedConveyer : public Conveyer
{
private:

	char direction;

	bool isPositionFree[5];

public:

	ShieldedConveyer(char v_type, char v_direction, short v_durability, short v_size, int tileX, int tileY);
	ShieldedConveyer();
	~ShieldedConveyer() = default;

	void load(std::ifstream& fin) override;

	void draw(sf::RenderWindow& window) override;
	
};


#endif // SHIELDED_CONVEYER_H
