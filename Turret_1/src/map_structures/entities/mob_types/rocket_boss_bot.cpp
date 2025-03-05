
#include "rocket_boss_bot.h"

#include "map_structures/team/team.h"
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/entities/behavior/aiming.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"
#include "t1_system/events/events_handler.h"

constexpr int TILE_RANGE = 28;
const int PIXEL_RANGE = t1::be::pixel(TILE_RANGE);
const int SPYRAL_RANGE = t1::be::tileRangeToSpiralRange[TILE_RANGE];

RocketBossBot::RocketBossBot(Team* const team) : Entity(team)
{
	durability = 230 * world->getPreSettings().getMobs().maxDurabilityModifier;
}


void RocketBossBot::shoot(const BuildingsMap& buildingsMap)
{
	Entity::reloadWeapon();

	if (tileJustChanged || EventsHandler::active(t1::EventType::MAP_CHANGED))
		aimCoord = Aiming::aimOnBuilding(*this, SPYRAL_RANGE, world->getBuildingsMap());

	if (aimCoord.valid())
	{
		shootingAngleRad = atan2f(aimCoord.x - coord.x, aimCoord.y - coord.y);
		shootingAngleDeg = t1::be::radToDegree(shootingAngleRad);

		if (reloadTimer <= 0)
		{
			float correctionX = cos(shootingAngleRad) * 18.0f;
			float correctionY = sin(shootingAngleRad) * 18.0f;

			team->spawnShell(ShellType::ROCKET, { coord.x - correctionX, coord.y + correctionY }, shootingAngleRad, shootingAngleDeg);
			team->spawnShell(ShellType::ROCKET, { coord.x + correctionX, coord.y - correctionY }, shootingAngleRad, shootingAngleDeg);
			reloadTimer = 60;
		}
		else if (reloadTimer == 30)
		{
			float correctionX = cos(shootingAngleRad) * 14.0f;
			float correctionY = sin(shootingAngleRad) * 14.0f;

			team->spawnShell(ShellType::ROCKET, { coord.x - correctionX, coord.y + correctionY }, shootingAngleRad, shootingAngleDeg);
			team->spawnShell(ShellType::ROCKET, { coord.x + correctionX, coord.y - correctionY }, shootingAngleRad, shootingAngleDeg);
		}
	}
}


void RocketBossBot::draw(sf::RenderWindow& window)
{
	entitySprite.setTextureRect(sf::IntRect(0, 62, 47, 30));
	entitySprite.setOrigin(24, 14);

	if (aimCoord.valid())
		entitySprite.setRotation(shootingAngleDeg);
	else
		entitySprite.setRotation(motionAngleDeg);

	entitySprite.setPosition(coord.x, coord.y);
	window.draw(entitySprite);

	if (durability > 110)    //Boss_energy_shield
	{
		shieldSprite.setPosition(coord.x, coord.y);
		window.draw(shieldSprite);
	}
}
