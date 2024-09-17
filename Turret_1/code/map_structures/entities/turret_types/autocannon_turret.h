#pragma once
#ifndef AUTOCANNON_TURRET_H
#define AUTOCANNON_TURRET_H

#include <SFML\Graphics.hpp>

#include "../turrets.h"


class AutocannonTurret : public Turret
{
	public:
		
		AutocannonTurret(char turretType ,int tileX, int tileY, float curentAngle, short curentDurability);
		AutocannonTurret(int turretType);
		~AutocannonTurret();

		void shooting() override;
		
		bool needAmoo() override;
		void takeAmoo(int resType) override;
		int getAmooType() override;
		
		void draw(sf::RenderWindow& window) override;

};


#endif // AUTOCANNON_TURRET_H
