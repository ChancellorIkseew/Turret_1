
#include <SFML\Graphics.hpp>


#include "autocannon_turret.h"

#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/resources/res_enum.h"

#include "map_structures/entities/entities_util/entities_list.h"
#include "map_structures/shells/shells.h"
#include "map_structures/shells/shell_enum.h"


AutocannonTurret::AutocannonTurret(int type) : Turret()
{
	pixelRange = 11* _TILE_;
}

AutocannonTurret::AutocannonTurret(int type ,int tileX, int tileY, float curentAngle, short curentDurability) :
	Turret(AUTOCANNON_TURRET, tileX, tileY, curentAngle, curentDurability)
{
	pixelRange = 11 * _TILE_;
}

		
void AutocannonTurret::shooting()
{
	if(this->findAim())
	{
		angleRad = atan2f(aimCoordX - coordX, aimCoordY - coordY);
		angleDeg = atan2f(aimCoordY - coordY, aimCoordX - coordX) * 57.3f + 90.0f;

		if (reloadTimer % 15 == 0 && amooQuant > 0)		//shooting
		{
			float correctionX = cos(angleRad) * 1.5f;
			float correctionY = sin(angleRad) * 1.5f;

			if (reloadTimer % 30 == 0)
			{
				playerShellsList.push_back(new Shell(AC_SHELL, coordX + correctionX, coordY - correctionY, angleRad, angleDeg));
				reloadTimer = 0;
			}
			else
			{
				playerShellsList.push_back(new Shell(AC_SHELL, coordX - correctionX, coordY + correctionY, angleRad, angleDeg));
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
}
