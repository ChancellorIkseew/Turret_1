
#include "laser_bot.h"

#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/entities/behavior/aiming.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"

constexpr int TILE_RANGE = 8;
const float PIXEL_RANGE = t1::be::pixelF(TILE_RANGE);
const int SPYRAL_RANGE = t1::be::tileRangeToSpiralRange[TILE_RANGE];

LaserBot::LaserBot(Team* const team) : Entity(team)
{
	durability = 10 * world->getPreSettings().getMobs().maxDurabilityModifier;
}


void LaserBot::shoot(const BuildingsMap& buildingsMap)
{
	Entity::reloadWeapon();
	Entity::aim(SPYRAL_RANGE, PIXEL_RANGE);

	PixelCoord newAim = Aiming::aimOnShell(*this, PIXEL_RANGE, *world);
	if (newAim.valid())
		aimCoord = newAim;

	if (aimCoord.valid())
	{
		shootingAngleRad = atan2f(aimCoord.x - coord.x, aimCoord.y - coord.y);
		shootingAngleDeg = t1::be::radToDegree(shootingAngleRad);

		if (reloadTimer <= 0)
		{
			team->spawnShell(ShellType::LASER, coord, shootingAngleRad, shootingAngleDeg);
			reloadTimer = 2;
		}
	}
}


void LaserBot::draw(sf::RenderWindow& window)
{
	entitySprite.setTextureRect(sf::IntRect(60, 0, 17, 15));
	entitySprite.setOrigin(9, 8);

	if (aimCoord.valid())
		entitySprite.setRotation(shootingAngleDeg);
	else
		entitySprite.setRotation(motionAngleDeg);

	entitySprite.setPosition(coord.x, coord.y);
	window.draw(entitySprite);
}
