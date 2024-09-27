#pragma once
#ifndef ROCKET_H
#define ROCKET_H

#include <SFML\Graphics.hpp>

#include "map_structures/shells/shell/shell.h"


class Rocket : public Shell
{
	public:
		Rocket(short type, PixelCoord coord, float angleRad, float angleDeg);
		~Rocket() = default;

		void tryPlayerShellsHitting() override final;
		void tryEnemyShellsHitting() override final;
		void explosion() override final;

		void draw(sf::RenderWindow& window, int time) override final;
		
};

#endif // ROCKETS_H
