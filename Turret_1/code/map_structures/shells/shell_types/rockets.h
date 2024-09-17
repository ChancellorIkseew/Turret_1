#pragma once

#ifndef ROCKETS_H
#define ROCKETS_H

#include <iostream>
#include <string>
#include <SFML\Graphics.hpp>
#include <list>

#include "../../buildings/buildings_map.h"
#include "../shells.h"



class Rocket : public Shell
{
	private:
		
	
	public:
		
		Rocket(char v_shellType ,float v_coordX, float v_coordY, float v_angleRad, float v_angleDeg);
		
		//void prepareTextures();

		void tryPlayerShellsHitting(BuildingsMap& buildingsMap1) override;

		void tryEnemyShellsHitting(BuildingsMap& buildingsMap1) override;

		void explosion(BuildingsMap& buildingsMap1) override;

		void drawShell(sf::RenderWindow& window, int time) override;
		
		~Rocket();
};

#endif // ROCKETS_H