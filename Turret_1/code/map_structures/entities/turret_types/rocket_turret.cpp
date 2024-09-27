
#include <SFML\Graphics.hpp>


#include "rocket_turret.h"

#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/resources/res_enum.h"

#include "map_structures/entities/entities_util/entities_list.h"
#include "map_structures/shells/shells_list/shells_list.h"
#include "map_structures/shells/shell/shell.h"
#include "map_structures/shells/shell/shell_enum.h"


RocketTurret::RocketTurret(int type) : Turret()
{
	pixelRange = 35 * _TILE_;
}

RocketTurret::RocketTurret(int type ,int tileX, int tileY, float curentAngle, short curentDurability) :
	Turret(ROCKET_TURRET, tileX, tileY, curentAngle, curentDurability)
{
	pixelRange = 35 * _TILE_;
}


void RocketTurret::shooting()
{
	if(this->findAim())
	{
		angleRad = atan2f(aimCoordX - coordX, aimCoordY - coordY);
		angleDeg = atan2f(aimCoordY - coordY, aimCoordX - coordX) * 57.3f + 90.0f;

		if (reloadTimer > 120 && amooQuant > 0)		//shooting
		{
			t1::sh::playerShellsList.push_back(Shell::createShell(ROCKET, { float(coordX), float(coordY) }, angleRad, angleDeg));
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
}
