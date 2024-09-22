#pragma once
#ifndef ROCKET_H
#define ROCKET_H

#include <SFML\Graphics.hpp>

#include "map_structures/buildings/buildings_map.h"
#include "map_structures/shells/shells.h"


class Rocket : public Shell
{
	public:
		
		Rocket(int type ,float coordX, float coordY, float angleRad, float angleDeg);
		~Rocket() = default;

		void tryPlayerShellsHitting(BuildingsMap& buildingsMap1) override final;
		void tryEnemyShellsHitting(BuildingsMap& buildingsMap1) override final;
		void explosion(BuildingsMap& buildingsMap1) override final;

		void draw(sf::RenderWindow& window, int time) override final;
		
};

#endif // ROCKETS_H
