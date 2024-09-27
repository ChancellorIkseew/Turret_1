
#include <fstream>
#include <SFML\Graphics.hpp>

#include "entity.h"

#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/pre-settings/pre-settings.h"

using namespace t1::be;

void Entity::initPreSettings()
{
	Entity::mapMaxX = PreSettings::mapMaxX;
	Entity::mapMaxY = PreSettings::mapMaxY;
	Entity::enemyMobMaxDurabilityModifier = PreSettings::enemyMobMaxDurabilityModifier;
}

Entity::Entity(const int type)		//1st spawn
{
	this->type = type;
	isAimDetected = false;
	aimCoord = pixel(mapMaxX / 2, mapMaxY / 2);
	destCoord = aimCoord;
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


void Entity::motion()
{
	this->motionAngleRad = atan2f(destCoord.x - coord.x, destCoord.y - coord.y);
	this->motionAngleDeg = atan2f(destCoord.y - coord.y, destCoord.x - coord.x) * 57.3f + 90.0f;

	int nextTileX = tile(coord.x + sin(motionAngleRad) * 30);
	int nextTileY = tile(coord.y + cos(motionAngleRad) * 30);

	if ((BuildingsMap::isVoidBuilding(nextTileX, nextTileY)))
	{
		this->coord.x += sin(motionAngleRad) * maxSpeed;
		this->coord.y += cos(motionAngleRad) * maxSpeed;
	}
	else
	{
		destCoord = this->findDestinationCoord();
	}

	if (newTile.x != oldTile.x || newTile.y != oldTile.y)
	{
		destCoord = pixel(mapMaxX / 2, mapMaxY / 2);
	}

	this->oldTile = this->newTile;
	this->newTile = tile(coord);
}


PixelCoord Entity::findDestinationCoord() const
{
	int minDistance = pow((newTile.x - 50), 2) + pow((newTile.y - 50), 2);

	for (int i = 1; i < 9; i += 2)
	{
		int tileX = this->newTile.x + coordSpyralArr[i].x;
		int tileY = this->newTile.y + coordSpyralArr[i].y;

		if (BuildingsMap::isVoidBuilding(tileX, tileY))
		{
			int distance = pow((tileX - mapMaxX / 2), 2) + pow((tileY - mapMaxX / 2), 2);
			if (distance < minDistance)
			{
				return pixel(tileX, tileY);
			}
		}
	}
	return pixel(mapMaxX / 2, mapMaxY / 2);
}


PixelCoord Entity::findShootingAim() const
{
	for (int i = 1; i <= range; i++)
	{
		int tileX = tile(coord.x + sin(motionAngleRad) * _TILE_ * i);
		int tileY = tile(coord.y + cos(motionAngleRad) * _TILE_ * i);
		TileCoord tileCoord{ tileX, tileY };
		if (BuildingsMap::buildingExists(tileCoord))
		{
			return pixel(tileCoord);
		}
	}

	for (int i = 0; i < spyralRange; i++)
	{
		int tileX = this->newTile.x + coordSpyralArr[i].x;
		int tileY = this->newTile.y + coordSpyralArr[i].y;
		TileCoord tileCoord{ tileX, tileY };
		if (BuildingsMap::buildingExists(tileCoord))
		{
			return pixel(tileCoord);
		}
	}

	return { 0.0f, 0.0f };
}


void Entity::detectAim()
{
	if (newTile.x != oldTile.x || newTile.y != oldTile.y || BuildingsMap::getIsMapChanged())
	{
		PixelCoord newAimCoord = this->findShootingAim();
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


void Entity::setDurability(const int durability)
{
	this->durability = durability;
}

void Entity::setDamage(const int damage)
{
	durability -= damage;
}

void Entity::setCoord(const PixelCoord coord)
{
	this->coord = coord;
}


char Entity::getType() const { return type; }
PixelCoord Entity::getCoord() const { return coord; }
TileCoord Entity::getTile() const { return tile(coord); }
int Entity::getAngleDeg() const { return int(motionAngleDeg); }
int Entity::getDurability() const { return durability; }


// visual
void Entity::prepareSprites()
{
	entityImage.loadFromFile("images/flame_bot.bmp");
	entityImage.createMaskFromColor(sf::Color(0, 255, 0));
	entityTexture.loadFromImage(entityImage);
	entitySprite.setTexture(entityTexture);
	entitySprite.setTextureRect(sf::IntRect(1, 1, 15, 13));
	entitySprite.setOrigin(8, 7);

	shieldImage.loadFromFile("images/shield.bmp");
	shieldImage.createMaskFromColor(sf::Color(0, 255, 0));
	shieldTexture.loadFromImage(shieldImage);
	shieldSprite.setTexture(shieldTexture);
	shieldSprite.setTextureRect(sf::IntRect(0, 0, 49, 48));
	shieldSprite.setOrigin(24, 24);
	shieldSprite.setColor(sf::Color(255, 255, 255, 128));
}
