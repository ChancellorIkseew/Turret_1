
#include "entity.h"

#include "map_structures/team/team.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/pre-settings/pre-settings.h"
#include "t1_system/events/events_handler.h"

using namespace t1::be;
constexpr float BASIC_COLLISION_RADIUS = 30.0f;

void Entity::initPreSettings()
{
	Entity::mapSize = PreSettings::getTerrain().mapSize;
	Entity::maxDurabilityModifier = PreSettings::getMobs().maxDurabilityModifier;
}

Entity::Entity(const uint16_t type, Team* const team)		//1st spawn
{
	this->type = type;
	this->team = team;
	isAimDetected = false;
	aimCoord = destCoord;
	reloadTimer = 0;
	maxSpeed = 0.1f;
}


void Entity::save(cereal::BinaryOutputArchive& archive) const
{
	archive(type);
	archive(coord);
	archive(motionAngleDeg);
	archive(durability);
}

void Entity::load(cereal::BinaryInputArchive& archive)
{
	archive(type);
	archive(coord);
	archive(motionAngleDeg);
	archive(durability);
}


bool Entity::tileChanged() const
{
	return currentTile.x != oldTile.x || currentTile.y != oldTile.y;
}


void Entity::motion(const BuildingsMap& buildingsMap)
{
	this->motionAngleRad = atan2f(destCoord.x - coord.x, destCoord.y - coord.y);
	this->motionAngleDeg = t1::be::radToDegree(motionAngleRad);

	int nextTileX = tile(coord.x + sin(motionAngleRad) * BASIC_COLLISION_RADIUS);
	int nextTileY = tile(coord.y + cos(motionAngleRad) * BASIC_COLLISION_RADIUS);

	if (buildingsMap.isVoidBuilding(nextTileX, nextTileY))
	{
		this->coord.x += sin(motionAngleRad) * maxSpeed;
		this->coord.y += cos(motionAngleRad) * maxSpeed;
	}
	else
	{
		destCoord = pixel(t1::ent::findDestination(*this, buildingsMap));
	}

	if (tileChanged())
	{
		destCoord = pixel(t1::ent::findClosestCore(*this, buildingsMap));
	}

	this->oldTile = this->currentTile;
	this->currentTile = tile(coord);
}


void Entity::detectAim(const BuildingsMap& buildingsMap)
{
	if (tileChanged() || EventsHandler::active(t1::EventType::MAP_CHANGED))
	{
		PixelCoord newAimCoord = t1::ent::findAim(*this, buildingsMap);
		if (newAimCoord.x != 0)	// "0" - aim_was_not_detected
		{
			aimCoord = newAimCoord;
			isAimDetected = true;
		}
		else
		{
			isAimDetected = false;
		}
	}
}


void Entity::reloadWeapon()
{
	if (reloadTimer > 0)
		--reloadTimer;
}


void Entity::setDurability(const int16_t durability)
{
	this->durability = durability;
}

void Entity::setDamage(const int16_t damage)
{
	durability -= damage;
}

void Entity::setCoord(const PixelCoord coord)
{
	this->coord = coord;
}

void Entity::setDestCoord(const PixelCoord destCoord)
{
	this->destCoord = destCoord;
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
