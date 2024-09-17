#pragma once
#ifndef ROCKET_FACTORY_H
#define ROCKET_FACTORY_H

#include "../factory.h"
//#include "../../../buildings_map.h"

#include "SFML/Graphics.hpp"


class RocketFactory : public Factory
{
protected:

public:

	RocketFactory(int v_type, short v_durability, short v_size, int tileX, int tileY);
	RocketFactory();
	~RocketFactory();

	void interact() override;
	void produceResource() override;

	bool canAccept(int resType) override;
	bool isThisPositionFree(int position) override;

	void animation();
	void draw(sf::RenderWindow& window) override;

	
};



#endif // ROCKET_FACTORY_H