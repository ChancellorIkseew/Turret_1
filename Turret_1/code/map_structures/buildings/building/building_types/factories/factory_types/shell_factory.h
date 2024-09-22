#pragma once
#ifndef SHELL_FACTORY_H
#define SHELL_FACTORY_H

#include "../factory.h"

#include "SFML/Graphics.hpp"


class ShellFactory final : public Factory
{
protected:

public:

	ShellFactory(int type, short durability, short size, int tileX, int tileY);
	ShellFactory();
	~ShellFactory() = default;

	void interact() override;
	void produceResource() override;

	bool canAccept(int resType) override;

	void animation();
	void draw(sf::RenderWindow& window) override;

};


#endif // SHELL_FACTORY_H
