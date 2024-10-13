
#include <SFML\Graphics.hpp>


#include "autocannon_turret.h"

#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/resources/res_enum.h"
<<<<<<< Updated upstream

#include "map_structures/entities/entities_list/entities_list.h"
=======
>>>>>>> Stashed changes
#include "map_structures/shells/shell/shell_enum.h"


AutocannonTurret::AutocannonTurret(int type, TileCoord tile) :
	Turret(AUTOCANNON_TURRET, tile)
{
	pixelRange = 11 * _TILE_;
	maxAmoo = 181;
}

		
void AutocannonTurret::shooting()
{
	Turret::reloadWeapon();
	PixelCoord aim = Turret::findShootingAim();
	if(aim.x != 0)
	{
		angleRad = atan2f(aim.x - coord.x, aim.y - coord.y);
		angleDeg = atan2f(aim.y - coord.y, aim.x - coord.x) * 57.3f + 90.0f;

		if (reloadTimer % 15 == 0 && amooQuantity > 0)
		{
			float correctionX = cos(angleRad) * 1.5f;
			float correctionY = sin(angleRad) * 1.5f;

			if (reloadTimer <= 0)
			{
				//t1::sh::playerShellsList.emplace_back(Shell::createShell(AC_SHELL, { coord.x + correctionX, coord.y - correctionY }, angleRad, angleDeg));
				reloadTimer = 30;
			}
			else
			{
				//t1::sh::playerShellsList.emplace_back(Shell::createShell(AC_SHELL, { coord.x - correctionX, coord.y + correctionY }, angleRad, angleDeg));
			}
			--amooQuantity;
		}
	}
}


void AutocannonTurret::takeAmoo(int resType) { amooQuantity += 20; }
int AutocannonTurret::getAmooType() const { return RES_AC_SHELLS; }


void AutocannonTurret::draw(sf::RenderWindow& window)
{
	turretSprite.setTextureRect(sf::IntRect(4, 5, 12, 20));
	turretSprite.setOrigin(5.5, 12);

	turretSprite.setPosition(coord.x, coord.y);
	turretSprite.setRotation(angleDeg);
	window.draw(turretSprite);
}
