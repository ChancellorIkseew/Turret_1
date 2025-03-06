
#include "rocket_bot.h"

#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/entities/behavior/aiming.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"
#include "t1_system/events/events_handler.h"

constexpr int TILE_RANGE = 25;
const float PIXEL_RANGE = t1::be::pixelF(TILE_RANGE);
const int SPYRAL_RANGE = t1::be::tileRangeToSpiralRange[TILE_RANGE];

RocketBot::RocketBot(Team* const team) : Entity(team)
{
	durability = 25 * world->getPreSettings().getMobs().maxDurabilityModifier;
}


void RocketBot::shoot()
{
	if (!aimCoord.valid())
		return;
	shootingAngleRad = atan2f(aimCoord.x - coord.x, aimCoord.y - coord.y);
	shootingAngleDeg = t1::be::radToDegree(shootingAngleRad);

	if (reloadTimer > 0)
		return;
	float correctionX = cos(shootingAngleRad) * 5.0f;
	float correctionY = sin(shootingAngleRad) * 5.0f;
	team->spawnShell(ShellType::ROCKET, { coord.x - correctionX, coord.y + correctionY }, shootingAngleRad, shootingAngleDeg);
	reloadTimer = 240;
}

void RocketBot::shootByOwnAI()
{
	if (tileJustChanged || EventsHandler::active(t1::EventType::MAP_CHANGED))
		aimCoord = Aiming::aimOnBuilding(*this, SPYRAL_RANGE, world->getBuildingsMap());
	shoot();
}


void RocketBot::draw(sf::RenderWindow& window)
{
	entitySprite.setTextureRect(sf::IntRect(42, 0, 17, 18));
	entitySprite.setOrigin(8, 9);

	if (aimCoord.valid())
		entitySprite.setRotation(shootingAngleDeg);
	else
		entitySprite.setRotation(motionAngleDeg);

	entitySprite.setPosition(coord.x, coord.y);
	window.draw(entitySprite);
}
