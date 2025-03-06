
#include "standard_bot.h"

#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"

constexpr int TILE_RANGE = 5;
const float PIXEL_RANGE = t1::be::pixelF(TILE_RANGE);
const int SPYRAL_RANGE = t1::be::tileRangeToSpiralRange[TILE_RANGE];

StandardBot::StandardBot(Team* const team) : Entity(team)
{
	durability = 10 * world->getPreSettings().getMobs().maxDurabilityModifier;
}


void StandardBot::shoot()
{
	if (!aimCoord.valid())
		return;
	shootingAngleRad = atan2f(aimCoord.x - coord.x, aimCoord.y - coord.y);
	shootingAngleDeg = t1::be::radToDegree(shootingAngleRad);

	if (reloadTimer > 0)
		return;
	float correctionX = cos(shootingAngleRad) * 4.5f;
	float correctionY = sin(shootingAngleRad) * 4.5f;	
	team->spawnShell(ShellType::AC_SHELL, { coord.x - correctionX, coord.y + correctionY }, shootingAngleRad, shootingAngleDeg);
	reloadTimer = 30;
}

void StandardBot::shootByOwnAI()
{
	Entity::aim(SPYRAL_RANGE, PIXEL_RANGE);
	shoot();
}


void StandardBot::draw(sf::RenderWindow& window)
{
	entitySprite.setTextureRect(sf::IntRect(1, 1, 15, 13));
	entitySprite.setOrigin(8, 7);

	if (aimCoord.valid())
		entitySprite.setRotation(shootingAngleDeg);
	else
		entitySprite.setRotation(motionAngleDeg);

	entitySprite.setPosition(coord.x, coord.y);
	window.draw(entitySprite);
}
