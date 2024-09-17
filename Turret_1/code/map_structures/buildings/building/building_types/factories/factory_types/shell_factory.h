#pragma once
#ifndef SHELL_FACTORY_H
#define SHELL_FACTORY_H

#include "../factory.h"
//#include "../../../buildings_map.h"

#include "SFML/Graphics.hpp"


class ShellFactory : public Factory
{
protected:

public:

	ShellFactory(int v_type, short v_durability, short v_size, int tileX, int tileY);
	ShellFactory();
	~ShellFactory();

	void interact() override;
	void produceResource() override;

	bool canAccept(int resType) override;
	bool isThisPositionFree(int position) override;

	void animation();
	void draw(sf::RenderWindow& window) override;

};


#endif // SHELL_FACTORY_H
