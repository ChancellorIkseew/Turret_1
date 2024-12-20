
#include "entity.h"

#include "map_structures/team/team.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/pre-settings/pre-settings.h"
#include "t1_system/events/events_handler.h"

#include "iostream"

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
	destCoord = pixel(t1::ent::findClosestCore(*this));
	aimCoord = destCoord;
	reloadTimer = 0;
	maxSpeed = 0.1f;
}


void Entity::save(std::ofstream& fout) const
{
	fout << type << " " << coord.x << " " << coord.y << " " << motionAngleDeg << " " << durability << '\n';
	fout << "$\n";
}

void Entity::load(std::ifstream& fin)
{
	fin >> coord.x >> coord.y >> motionAngleDeg >> durability;
	char specialSymbol;
	fin >> specialSymbol;
}


bool Entity::tileChanged() const
{
	return currentTile.x != oldTile.x || currentTile.y != oldTile.y;
}


void Entity::motion()
{
	this->motionAngleRad = atan2f(destCoord.x - coord.x, destCoord.y - coord.y);
	this->motionAngleDeg = t1::be::radToDegree(motionAngleRad);

	int nextTileX = tile(coord.x + sin(motionAngleRad) * BASIC_COLLISION_RADIUS);
	int nextTileY = tile(coord.y + cos(motionAngleRad) * BASIC_COLLISION_RADIUS);

	if (BuildingsMap::isVoidBuilding(nextTileX, nextTileY))
	{
		this->coord.x += sin(motionAngleRad) * maxSpeed;
		this->coord.y += cos(motionAngleRad) * maxSpeed;
	}
	else
	{
		destCoord = pixel(t1::ent::findDestination(*this));
	}

	if (tileChanged())
	{
		destCoord = pixel(t1::ent::findClosestCore(*this));
	}

	this->oldTile = this->currentTile;
	this->currentTile = tile(coord);
}


void Entity::detectAim()
{
	if (tileChanged() || EventsHandler::active(t1::EventType::MAP_CHANGED))
	{
		PixelCoord newAimCoord = t1::ent::findAim(*this);
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


uint16_t Entity::getType() const { return type; }
PixelCoord Entity::getCoord() const { return coord; }
TileCoord Entity::getTile() const { return tile(coord); }
int Entity::getAngleDeg() const { return int(motionAngleDeg); }
int Entity::getDurability() const { return durability; }


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
