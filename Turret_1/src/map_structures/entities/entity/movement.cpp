
#include "entity.h"

#include "map_structures/world/world.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/entities/behavior/path_finding.h"
#include "map_structures/entities/behavior/comon.h"
#include "t1_system/events/events_handler.h"

constexpr float BASIC_COLLISION_RADIUS = 30.0f;
constexpr float MAX_SPEED = 0.1; // temporary desision

void Entity::checkTileChanged()
{
	const TileCoord newTile = t1::be::tile(coord);
	tileJustChanged = !(currentTile == newTile);
	if (tileJustChanged)
		currentTile = newTile;
}


void Entity::changeLineMotion(const float speed)
{
	lineMotion.x = sin(motionAngleRad) * speed;
	lineMotion.y = cos(motionAngleRad) * speed;
}


void Entity::calculateMotion(const BuildingsMap& buildingsMap)
{
	checkTileChanged();

	if (EventsHandler::active(t1::EventType::MAP_CHANGED)) //will be expanded to MAP_CANGED.coresChanged()
		destCoord = PathFinding::findClosestCore(currentTile, buildingsMap);

	if (tileJustChanged || EventsHandler::active(t1::EventType::MAP_CHANGED)) //will be expanded to MAP_CANGED close to this mob
	{
		const PixelCoord dest = t1::be::pixel(destCoord);
		motionAngleRad = atan2(dest.x - coord.x, dest.y - coord.y);
		nextTile = Comon::findDirectPahtNextTile(coord, currentTile, motionAngleRad);
		changeLineMotion(MAX_SPEED);
	}
	
	if (!buildingsMap.isVoidBuilding(nextTile))
	{
		nextTile = PathFinding::findNextTile(currentTile, destCoord, buildingsMap);
		const PixelCoord nextTileCenter = t1::be::pixel(nextTile);
		motionAngleRad = atan2(nextTileCenter.x - coord.x, nextTileCenter.y - coord.y);
		changeLineMotion(MAX_SPEED);
	}
}

void Entity::moveByDirectControl(const PixelCoord vector)
{
	if (vector == PixelCoord(0, 0))
		return;
	coord = coord + vector * MAX_SPEED;
	motionAngleRad = atan2(vector.x, vector.y);
}

void Entity::moveByOwnAI()
{
	BuildingsMap& map = world->getBuildingsMap();
	calculateMotion(map);
	if (destCoord.valid() && !(nextTile == currentTile) && map.isVoidBuilding(nextTile))
		coord = coord + lineMotion;
}