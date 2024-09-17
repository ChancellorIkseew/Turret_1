#pragma once
#ifndef ROCKET_TURRET_H
#define ROCKET_TURRET_H

#include <SFML\Graphics.hpp>

#include "../turrets.h"


class RocketTurret : public Turret
{
	public:
		
		RocketTurret(char turretType ,int tileX, int tileY, float curentAngle, short curentDurability);
		RocketTurret(int turretType);
		~RocketTurret();

		void shooting() override;
		
		bool needAmoo() override;
		void takeAmoo(int resType) override;
		int getAmooType() override;
		
		void draw(sf::RenderWindow& window) override;

};


#endif // ROCKET_TURRET_H
