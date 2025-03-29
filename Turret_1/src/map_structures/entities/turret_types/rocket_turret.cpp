
#include "rocket_turret.h"

#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/team/team.h"

constexpr int TILE_RANGE = 34;
const float PIXEL_RANGE = t1::be::pixelF(TILE_RANGE);
const int SPYRAL_RANGE = t1::be::tileRangeToSpiralRange[TILE_RANGE];

RocketTurret::RocketTurret(const TileCoord tile, Team* const team) :
	Turret(tile, team) { }


void RocketTurret::shooting()
{
	Turret::reloadWeapon();
	Turret::aim(SPYRAL_RANGE, PIXEL_RANGE);
	if (aimCoord.valid())
	{
		angleRad = atan2f(aimCoord.x - coord.x, aimCoord.y - coord.y);

		if (reloadTimer <= 0 && amooQuantity > 0)
		{
			team->spawnShell(ShellType::ROCKET, coord, angleRad);
			reloadTimer = 120;
			--amooQuantity;
		}
	}
}


void RocketTurret::takeAmoo(ResType resType) { amooQuantity += 1; }
ResType RocketTurret::getAmooType() const { return ResType::ROCKET; }


void RocketTurret::draw(sf::RenderWindow& window)
{
	turretSprite.setTextureRect(sf::IntRect({ 4, 25 }, { 12, 18 }));
	turretSprite.setOrigin({ 5.5, 11 });

	turretSprite.setPosition({ coord.x, coord.y });
	turretSprite.setRotation(sf::radians(PI - angleRad));
	window.draw(turretSprite);
}
