#pragma once
#ifndef CORE_H
#define CORE_H


#include "../../../buildings_map.h"
//#include "../../../buildings_map.h"

#include "SFML/Graphics.hpp"


class Core : public Building
{
protected:

public:

	Core(int v_type, short v_durability, short v_size, int tileX, int tileY);
	Core();
	virtual ~Core();

	void interact() override;

	bool canAccept(int resType) override;
	bool isThisPositionFree(int position) override;

	virtual void draw(sf::RenderWindow& window) override;
	
};


#endif // CORE_H
