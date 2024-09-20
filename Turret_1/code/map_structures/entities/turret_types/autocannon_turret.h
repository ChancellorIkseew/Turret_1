#pragma once
#ifndef AUTOCANNON_TURRET_H
#define AUTOCANNON_TURRET_H

#include <SFML\Graphics.hpp>

#include "map_structures/entities/turrets.h"


class AutocannonTurret : public Turret
{
	public:
		
		AutocannonTurret(int turretType ,int tileX, int tileY, float curentAngle, short curentDurability);
		AutocannonTurret(int turretType);
		~AutocannonTurret() = default;

		void shooting() override;
		
		bool needAmoo() override;
		void takeAmoo(int resType) override;
		int getAmooType() override;
		
		void draw(sf::RenderWindow& window) override;

};


#endif // AUTOCANNON_TURRET_H
