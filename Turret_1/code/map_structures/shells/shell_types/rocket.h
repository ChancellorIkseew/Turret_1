#pragma once
#ifndef ROCKET_H
#define ROCKET_H

#include <SFML\Graphics.hpp>

#include "map_structures/shells/shell/shell.h"


class Rocket : public Shell
{
	public:
		Rocket(PixelCoord coord, float angleRad, float angleDeg, Team* const team);
		Rocket() = default;
		~Rocket() = default;

		void tryHitting() override final;
		void explosion() override final;

		void draw(sf::RenderWindow& window) override final;
		
};

#endif // ROCKETS_H
