
#include <iostream>
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>
#include <cmath>
#include <list>


#include "rocket_turret.h"

#include "../../buildings/building/buildings_enum.h"

#include "../entities.h"
#include "../entities_util/entities_list.h"

#include "../../shells/shells.h"
#include "../../shells/shell_types/rockets.h"

#include "../../resources/res_enum.h"


RocketTurret::RocketTurret(int turretType) : Turret()
{
	pixelRange = 12* _TILE_;
}

RocketTurret::RocketTurret(char turretType ,int tileX, int tileY, float curentAngle, short curentDurability) :
	Turret(ROCKET_TURRET, tileX, tileY, curentAngle, curentDurability)
{
	pixelRange = 35 * _TILE_;
}

RocketTurret::~RocketTurret()
{

}



void RocketTurret::shooting()
{
	if(this->findAim())
	{
		angleRad = atan2f(aimCoordX - coordX, aimCoordY - coordY);
		angleDeg = atan2f(aimCoordY - coordY, aimCoordX - coordX) * 57.3 + 90;

		if (reloadTimer > 120 && amooQuant > 0)		//shooting
		{
			playerShellsList.push_back(new Rocket('3', coordX, coordY, angleRad, angleDeg));
			reloadTimer = 0;
			--amooQuant;
		}
		++reloadTimer;
	}
}

bool RocketTurret::needAmoo()
{
	if (amooQuant < 2)
	{
		return true;
	}
	return false;
}

void RocketTurret::takeAmoo(int resType)
{
	amooQuant = amooQuant + 1;
}

int RocketTurret::getAmooType()
{
	return RES_ROCKET;
}


void RocketTurret::draw(sf::RenderWindow& window)
{
	turretSprite.setTextureRect(sf::IntRect(4, 23, 12, 20));
	turretSprite.setOrigin(5.5, 12);

	turretSprite.setPosition(coordX, coordY);
	turretSprite.setRotation(angleDeg);
	window.draw(turretSprite);
	//std::cout << coordX << " " << coordY << '\n';
}