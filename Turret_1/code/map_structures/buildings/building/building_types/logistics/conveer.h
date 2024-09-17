#pragma once
#ifndef CONVEYER_H
#define CONVEYER_H

#include "../../../buildings_map.h"
#include "SFML/Graphics.hpp"

class Conveyer : public Building
{
private:

	char direction;

	bool isPositionFree[5];

public:

	Conveyer(char v_type, char v_direction, short v_durability, short v_size, int tileX, int tileY);
	Conveyer();
	virtual ~Conveyer();

	void save(std::ofstream& fout) override;
	virtual void load(std::ifstream& fin) override;

	bool canAccept(int resType) override;
	bool isThisPositionFree(int position) override;
	void leavePosition(int position) override;
	void takePosition(int position) override;

	virtual void draw(sf::RenderWindow& window) override;
	
};


#endif // CONVEYER_H
