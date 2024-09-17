
#include <iostream>
#include <SFML\Graphics.hpp>
#include <cmath>

#include "autocannon_turret.h"

#include "../../buildings/building/buildings_enum.h"

#include "../entities.h"
#include "../entities_util/entities_list.h"

#include "../../shells/shells.h"
#include "../../shells/shell_types/rockets.h"

#include "../../resources/res_enum.h"


AutocannonTurret::AutocannonTurret(int turretType) : Turret()
{
	pixelRange = 11* _TILE_;
}

AutocannonTurret::AutocannonTurret(char turretType ,int tileX, int tileY, float curentAngle, short curentDurability) :
	Turret(AUTOCANNON_TURRET, tileX, tileY, curentAngle, curentDurability)
{
	pixelRange = 11 * _TILE_;
}

AutocannonTurret::~AutocannonTurret()
{

}

		
void AutocannonTurret::shooting()
{
	if(this->findAim())
	{
		angleRad = atan2f(aimCoordX - coordX, aimCoordY - coordY);
		angleDeg = atan2f(aimCoordY - coordY, aimCoordX - coordX) * 57.3 + 90;

		if (reloadTimer % 15 == 0 && amooQuant > 0)		//shooting
		{
			float correctionX = cos(angleRad) * 1.5f;
			float correctionY = sin(angleRad) * 1.5f;

			if (reloadTimer % 30 == 0)
			{
				playerShellsList.push_back(new Shell('1', coordX + correctionX, coordY - correctionY, angleRad, angleDeg));
				reloadTimer = 0;
			}
			else
			{
				playerShellsList.push_back(new Shell('1', coordX - correctionX, coordY + correctionY, angleRad, angleDeg));
			}

			--amooQuant;
		}
		++reloadTimer;
	}
}



bool AutocannonTurret::needAmoo()
{
	if (amooQuant < 200)
	{
		return true;
	}
	return false;
}

void AutocannonTurret::takeAmoo(int resType)
{
	amooQuant = amooQuant + 20;
}

int AutocannonTurret::getAmooType() 
{
	return RES_AC_SHELLS;
}


void AutocannonTurret::draw(sf::RenderWindow& window)
{
	turretSprite.setTextureRect(sf::IntRect(4, 5, 12, 20));
	turretSprite.setOrigin(5.5, 12);

	turretSprite.setPosition(coordX, coordY);
	turretSprite.setRotation(angleDeg);
	window.draw(turretSprite);
	//std::cout << coordX << " " << coordY << '\n';
}
