#include "shuttle.h"

#include "map_structures/team/team.h"
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"
#include "t1_system/input/input_handler.h"

constexpr int TILE_RANGE = 20;
const float PIXEL_RANGE = t1::be::pixelF(TILE_RANGE);
const int SPYRAL_RANGE = t1::be::tileRangeToSpiralRange[TILE_RANGE];
constexpr float MAX_SPEED = 2.2;

Shuttle::Shuttle(Team* const team) : Entity(team)
{
	durability = 20 * world->getPreSettings().getMobs().maxDurabilityModifier;
}


void Shuttle::moveByOwnAI()
{
	motionAngleRad = atan2f(destCoord.x - coord.x, destCoord.y - coord.y);
	motionAngleDeg = t1::be::radToDegree(motionAngleRad);
	
	coord.x += sin(motionAngleRad) * MAX_SPEED;
	coord.y += cos(motionAngleRad) * MAX_SPEED;
}


void Shuttle::shoot()
{
	if (!aimCoord.valid())
		return;
	shootingAngleRad = atan2f(aimCoord.x - coord.x, aimCoord.y - coord.y);
	shootingAngleDeg = t1::be::radToDegree(shootingAngleRad);

	if (reloadTimer > 0)
		return;
	float correctionX = cos(shootingAngleRad) * 15.0f;
	float correctionY = sin(shootingAngleRad) * 15.0f;
	team->spawnShell(ShellType::LASER, coord, shootingAngleRad, shootingAngleDeg);
	reloadTimer = 2;
}

void Shuttle::shootByOwnAI()
{
	aim(SPYRAL_RANGE, PIXEL_RANGE);
	shoot();
}


void Shuttle::draw(sf::RenderWindow& window)
{
	entitySprite.setTextureRect(sf::IntRect(0, 18, 43, 43));
	entitySprite.setOrigin(22, 22);

	if (aimCoord.valid())
		entitySprite.setRotation(shootingAngleDeg);
	else
		entitySprite.setRotation(motionAngleDeg);

	entitySprite.setPosition(coord.x, coord.y);
	window.draw(entitySprite);

	if (durability > 150)    //Boss_energy_shield
	{
		shieldSprite.setPosition(coord.x, coord.y);
		window.draw(shieldSprite);
	}
}
