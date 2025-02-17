
#include "rocket_turret.h"

#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/team/team.h"


RocketTurret::RocketTurret(const TileCoord tile, Team* const team) :
	Turret(tile, team)
{
	spyralRange = 4109;
	pixelRange = 34 * _TILE_;
	maxAmoo = 2;
}


void RocketTurret::shooting()
{
	Turret::reloadWeapon();
	PixelCoord aim = Turret::findShootingAim();
	if (aim.x != 0)
	{
		angleRad = atan2f(aim.x - coord.x, aim.y - coord.y);
		angleDeg = atan2f(aim.y - coord.y, aim.x - coord.x) * 57.3f + 90.0f;

		if (reloadTimer <= 0 && amooQuantity > 0)
		{
			team->spawnShell(ShellType::ROCKET, { float(coord.x), float(coord.y) }, angleRad, angleDeg);
			reloadTimer = 120;
			--amooQuantity;
		}
	}
}


void RocketTurret::takeAmoo(int resType) { amooQuantity += 1; }
int RocketTurret::getAmooType() const { return RES_ROCKET; }


void RocketTurret::draw(sf::RenderWindow& window)
{
	turretSprite.setTextureRect(sf::IntRect(4, 23, 12, 20));
	turretSprite.setOrigin(5.5, 12);

	turretSprite.setPosition(coord.x, coord.y);
	turretSprite.setRotation(angleDeg);
	window.draw(turretSprite);
}
