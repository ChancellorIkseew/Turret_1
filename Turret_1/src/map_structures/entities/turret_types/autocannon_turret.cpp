
#include "autocannon_turret.h"

#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/team/team.h"

constexpr int TILE_RANGE = 11;
const float PIXEL_RANGE = t1::be::pixelF(TILE_RANGE);
const int SPYRAL_RANGE = t1::be::tileRangeToSpiralRange[TILE_RANGE];

AutocannonTurret::AutocannonTurret(const TileCoord tile, Team* const team) :
	Turret(tile, team) { }


void AutocannonTurret::shooting()
{
	Turret::reloadWeapon();
	Turret::aim(SPYRAL_RANGE, PIXEL_RANGE);
	if(aimCoord.valid())
	{
		angleRad = atan2f(aimCoord.x - coord.x, aimCoord.y - coord.y);

		if (reloadTimer % 15 == 0 && amooQuantity > 0)
		{
			float correctionX = cos(angleRad) * 1.5f;
			float correctionY = sin(angleRad) * 1.5f;

			if (reloadTimer <= 0)
			{
				team->spawnShell(ShellType::AC_SHELL, { coord.x + correctionX, coord.y - correctionY }, angleRad);
				reloadTimer = 30;
			}
			else
			{
				team->spawnShell(ShellType::AC_SHELL, { coord.x - correctionX, coord.y + correctionY }, angleRad);
			}
			--amooQuantity;
		}
	}
}


void AutocannonTurret::takeAmoo(ResType resType) { amooQuantity += 20; }
ResType AutocannonTurret::getAmooType() const { return ResType::AC_SHELLS; }


void AutocannonTurret::draw(sf::RenderWindow& window)
{
	turretSprite.setTextureRect(sf::IntRect({ 4, 5 }, { 12, 20 }));
	turretSprite.setOrigin({ 5.5, 12 });

	turretSprite.setPosition({ coord.x, coord.y });
	turretSprite.setRotation(sf::radians(PI - angleRad));
	window.draw(turretSprite);
}
