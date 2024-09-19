#pragma once
#ifndef ROCKETS_H
#define ROCKETS_H

#include <SFML\Graphics.hpp>

#include "map_structures/buildings/buildings_map.h"
#include "map_structures/shells/shells.h"


class Rocket : public Shell
{
	public:
		
		Rocket(char v_shellType ,float v_coordX, float v_coordY, float v_angleRad, float v_angleDeg);
		~Rocket() = default;

		void tryPlayerShellsHitting(BuildingsMap& buildingsMap1) override;
		void tryEnemyShellsHitting(BuildingsMap& buildingsMap1) override;
		void explosion(BuildingsMap& buildingsMap1) override;

		void draw(sf::RenderWindow& window, int time) override;
		
};


#endif // ROCKETS_H
