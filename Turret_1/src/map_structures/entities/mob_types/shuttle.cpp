#include "shuttle.h"

#include "map_structures/team/team.h"
#include "map_structures/shells/shell/shell_enum.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"
#include "t1_system/input/input_handler.h"
#include "map_structures/entities/behavior/path_finding.h"

constexpr int TILE_RANGE = 8;
const float PIXEL_RANGE = t1::be::pixelF(TILE_RANGE);
const int SPYRAL_RANGE = t1::be::tileRangeToSpiralRange[TILE_RANGE];
constexpr float MAX_SPEED = 2.2;

Shuttle::Shuttle(Team* team) : Entity(team)
{
	durability = 20 * world->getPreSettings().getMobs().maxDurabilityModifier;
}


void Shuttle::moveByOwnAI()
{
	BuildingsMap& map = world->getBuildingsMap();
	calculateMotion(map);
	
	if (currentTile == destCoord)
		world->getBlueprintsMap().constructBuilding(map, destCoord);
	if (destCoord.valid())
		coord = coord + lineMotion;
}


void Shuttle::calculateMotion(const BuildingsMap& buildingsMap)
{
	checkTileChanged();
	destCoord = PathFinding::findClosestBlueprint(currentTile, world->getBlueprintsMap());
	
	PixelCoord destCentre = t1::be::pixel(destCoord);
	motionAngleRad = atan2(destCentre.x - coord.x, destCentre.y - coord.y);
	changeLineMotion(MAX_SPEED);
}

void Shuttle::moveByDirectControl(const PixelCoord vector)
{
	coord = coord + vector * MAX_SPEED;
	motionAngleRad = atan2(vector.x, vector.y);
	checkTileChanged();
}

void Shuttle::shoot()
{
	if (!aimCoord.valid())
		return;
	shootingAngleRad = atan2f(aimCoord.x - coord.x, aimCoord.y - coord.y);

	if (reloadTimer > 0)
		return;
	float correctionX = cos(shootingAngleRad) * 15.0f;
	float correctionY = sin(shootingAngleRad) * 15.0f;
	team->spawnShell(ShellType::LASER, coord, shootingAngleRad);
	reloadTimer = 2;
}

void Shuttle::shootByOwnAI()
{
	aim(SPYRAL_RANGE, PIXEL_RANGE);
	shoot();
}

constexpr sf::Vector2f BOT_ORIGIN(9.0f, 8.0f);

void Shuttle::draw(sf::RenderWindow& window)
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
