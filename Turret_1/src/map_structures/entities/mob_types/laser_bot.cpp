
#include "laser_bot.h"

#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/entities/behavior/aiming.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"

constexpr int TILE_RANGE = 8;
const float PIXEL_RANGE = t1::be::pixelF(TILE_RANGE);
const int SPYRAL_RANGE = t1::be::tileRangeToSpiralRange[TILE_RANGE];

LaserBot::LaserBot(Team* team) : Entity(team)
{
	durability = 10 * world->getPreSettings().getMobs().maxDurabilityModifier;
}


void LaserBot::shoot()
{
	if (!aimCoord.valid())
		return;
	shootingAngleRad = atan2f(aimCoord.x - coord.x, aimCoord.y - coord.y);

	if (reloadTimer > 0)
		return;
	team->spawnShell(ShellType::LASER, coord, shootingAngleRad);
	reloadTimer = 2;
}

void LaserBot::shootByOwnAI()
{
	Entity::aim(SPYRAL_RANGE, PIXEL_RANGE);
	PixelCoord newAim = Aiming::aimOnShell(*this, PIXEL_RANGE, *world);
	if (newAim.valid())
		aimCoord = newAim;
	shoot();
}

constexpr sf::Vector2f BOT_ORIGIN(9.0f, 8.0f);

void LaserBot::draw(sf::RenderWindow& window)
{
	entitySprite.setTextureRect(sf::IntRect({ 60, 0 }, { 17, 15 }));
	entitySprite.setOrigin(BOT_ORIGIN);

	if (aimCoord.valid())
		entitySprite.setRotation(sf::radians(PI - shootingAngleRad));
	else
		entitySprite.setRotation(sf::radians(PI - motionAngleRad));

	entitySprite.setPosition({ coord.x, coord.y });
	window.draw(entitySprite);
}
