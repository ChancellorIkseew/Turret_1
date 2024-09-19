#pragma once
#ifndef FACTORY_H
#define FACTORY_H

#include "../../building.h"

#include "SFML/Graphics.hpp"


class Factory : public Building
{
protected:

	int timer;

public:

	Factory(int v_type, short v_durability, short v_size, int tileX, int tileY);
	Factory();
	virtual ~Factory() = default;

	void interact() override;
	virtual void produceResource() = 0;
	void placeResourceUnit(int type) override;

	virtual bool canAccept(int resType) override = 0;

	virtual void draw(sf::RenderWindow& window) override = 0;

};



#endif // SHELL_FACTORY_H
