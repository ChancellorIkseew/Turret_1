
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
