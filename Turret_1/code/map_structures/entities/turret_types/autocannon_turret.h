#pragma once
#ifndef AUTOCANNON_TURRET_H
#define AUTOCANNON_TURRET_H

#include <SFML\Graphics.hpp>

#include "map_structures/entities/turret/turret.h"


class AutocannonTurret : public Turret
{
	public:
		
		AutocannonTurret(int type ,int tileX, int tileY, float curentAngle, short curentDurability);
		AutocannonTurret(int type);
		~AutocannonTurret() = default;

		void shooting() override final;
		
		bool needAmoo() override final;
		void takeAmoo(int resType) override final;
		int getAmooType() override final;
		
		void draw(sf::RenderWindow& window) override final;

};

#endif // AUTOCANNON_TURRET_H
