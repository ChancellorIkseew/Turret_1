
#include "entity.h"

#include "map_structures/world/world.h"
#include "map_structures/team/team.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/entities/behavior/aiming.h"
#include "map_structures/entities/behavior/path_finding.h"
#include "t1_system/events/events_handler.h"
#include <iostream>

constexpr float BASIC_COLLISION_RADIUS = 30.0f;
constexpr float MAX_SPEED = 0.1; // temporary desision

Entity::Entity(Team* const team) : team(team), reloadTimer(0) { }

void Entity::save(cereal::BinaryOutputArchive& archive) const
{
	archive(coord, motionAngleRad, durability);
}

void Entity::load(cereal::BinaryInputArchive& archive)
{
	archive(coord, motionAngleRad, durability);
	motionAngleDeg = t1::be::radToDegree(motionAngleRad);
}


void Entity::checkTileChanged()
{
	const TileCoord newTile = t1::be::tile(coord);
	tileJustChanged = currentTile == newTile;
	if (tileJustChanged)
		currentTile = newTile;
}


void Entity::calculateMotion(const BuildingsMap& buildingsMap)
{
	checkTileChanged();

	if (EventsHandler::active(t1::EventType::MAP_CHANGED)) //will be expanded to MAP_CANGED.coresChanged()
		destCoord = PathFinding::findClosestCore(currentTile, buildingsMap);

	if (tileJustChanged || EventsHandler::active(t1::EventType::MAP_CHANGED))
	{
		const PixelCoord dest = t1::be::pixel(destCoord);
		motionAngleRad = atan2f(dest.x - coord.x, dest.y - coord.y);
		motionAngleDeg = t1::be::radToDegree(motionAngleRad);
		lineMotion.x = sin(motionAngleRad) * MAX_SPEED;
		lineMotion.y = cos(motionAngleRad) * MAX_SPEED;
		//Implement finding nextTile;
		PixelCoord line;
		line.x = sin(motionAngleRad) * BASIC_COLLISION_RADIUS;
		line.y = cos(motionAngleRad) * BASIC_COLLISION_RADIUS;
		nextTile = t1::be::tile(coord + line); // temporary implementation
	}

	if (!buildingsMap.isVoidBuilding(nextTile))
	{
		nextTile = PathFinding::findNextTile(currentTile, destCoord, buildingsMap);
		const PixelCoord nextTileCenter = t1::be::pixel(nextTile);
		motionAngleRad = atan2(nextTileCenter.x - coord.x, nextTileCenter.y - coord.y);
		motionAngleDeg = t1::be::radToDegree(motionAngleRad);
		lineMotion.x = sin(motionAngleRad) * MAX_SPEED;
		lineMotion.y = cos(motionAngleRad) * MAX_SPEED;
	}
}

void Entity::moveByDirectControl(const PixelCoord vector)
{
	coord = coord + vector * MAX_SPEED;
}

void Entity::moveByOwnAI()
{
	BuildingsMap& map = world->getBuildingsMap();
	calculateMotion(map);
	if (destCoord.valid() && !(nextTile == currentTile) && map.isVoidBuilding(nextTile))
		coord = coord + lineMotion;
}


void Entity::aim(const int spyralRange, const float pixelRange)
{
	if (tileJustChanged || EventsHandler::active(t1::EventType::MAP_CHANGED))
		aimCoord = INCORRECT_PIXEL_COORD;

	PixelCoord newAim;
	if (!aimCoord.valid())
	{
		newAim = Aiming::aimOnBuilding(*this, spyralRange, world->getBuildingsMap());
		if (newAim.valid())
			aimCoord = newAim;
	}

	newAim = Aiming::aimOnEntity(*this, pixelRange, *world);
	if (newAim.valid())
		aimCoord = newAim;
}


void Entity::reloadWeapon()
{
	if (reloadTimer > 0)
		--reloadTimer;
}

void Entity::setTeam(Team* team) {
	this->team = team;
}
void Entity::setDurability(const int16_t durability) {
	this->durability = durability;
}
void Entity::setDamage(const int16_t damage) {
	durability -= damage;
}
void Entity::setDamage(const float damage) {
	durability -= static_cast<int16_t>(damage);
}

void Entity::setControlType(Control controlType) {
	control = controlType;
}
void Entity::setCoord(const PixelCoord coord) {
	this->coord = coord;
}
void Entity::setDestCoord(const TileCoord destCoord) {
	this->destCoord = destCoord;
}
void Entity::setShootingAim(const PixelCoord aimCoord) {
	this->aimCoord = aimCoord;
}

// visual
void Entity::prepareSprites()
{
	entityImage.loadFromFile("images/mobs.bmp");
	entityImage.createMaskFromColor(sf::Color(0, 255, 0));
	entityTexture.loadFromImage(entityImage);
	entitySprite.setTexture(entityTexture);

	shieldImage.loadFromFile("images/shield.bmp");
	shieldImage.createMaskFromColor(sf::Color(0, 255, 0));
	shieldTexture.loadFromImage(shieldImage);
	shieldSprite.setTexture(shieldTexture);
	shieldSprite.setTextureRect(sf::IntRect(0, 0, 49, 48));
	shieldSprite.setOrigin(24, 24);
	shieldSprite.setColor(sf::Color(255, 255, 255, 128));
}
