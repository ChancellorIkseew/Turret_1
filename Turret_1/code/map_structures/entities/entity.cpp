
#include <fstream>
#include <SFML\Graphics.hpp>

#include "entity.h"
#include "mob_enum.h"
#include "map_structures/buildings/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/pre-settings/pre-settings.h"


int Entity::enemyMobsQuantity = 0;


void Entity::initPreSettings()
{
	Entity::mapMaxX = PreSettings::mapMaxX;
	Entity::mapMaxY = PreSettings::mapMaxY;
	Entity::enemyMobMaxDurabilityModifier = PreSettings::enemyMobMaxDurabilityModifier;
}

Entity::Entity(int type)		//1st spawn
{
	initCombatData();
	this->type = type;
	
	int x = rand() %4;
	switch(x)
	{
	case 0:
		coordX = pixel(0);
		coordY = pixel(rand() % (mapMaxY - 1));
		break;

	case 1:
		coordX = pixel(rand() % (mapMaxX - 3) + 1);
		coordY = pixel(0);
		break;

	case 2:
		coordX = pixel(mapMaxX - 1);
		coordY = pixel(rand() % (mapMaxY - 1));
		break;

	case 3:
		coordX = pixel(rand() % (mapMaxX - 3) + 1);
		coordY = pixel(mapMaxY - 1);
		break;

	default:
		coordX = pixel(0);
		coordY = pixel(0);
		break;
	}
	
}

Entity::Entity(int type ,float coordX, float coordY, float curentAngleDeg, short curentDurability)
{
	initCombatData();
	this->type = type;
	this->coordX = coordX;
	this->coordY = coordY;
	angleDeg = curentAngleDeg;
	durability = curentDurability;
}

Entity::~Entity()
{
	
}

void Entity::initCombatData()
{
	isAimDetected = false;

	aimCoordX = mapMaxX * _HALF_TILE_;
	aimCoordY = mapMaxY * _HALF_TILE_;

	destCoordX = aimCoordX;
	destCoordY = aimCoordY;

	maxSpeed = 0.1f;
}


void Entity::save(std::ofstream& fout)
{
	fout << type << " " << coordX << " " << coordY << " " << angleDeg << " " << durability << '\n';
	fout << "$\n";
}

void Entity::load(std::ifstream& fin)
{
	fin >> coordX >> coordY >> angleDeg >> durability;
	char specialSymbol;
	fin >> specialSymbol;
}


void Entity::motion(BuildingsMap &buildingsMap1, int time)
{

	angleRad = atan2f(destCoordX - coordX, destCoordY - coordY);
	angleDeg = atan2f(destCoordY - coordY, destCoordX - coordX) * 57.3f + 90;

	int tileCoordX = tile(coordX + sin(angleRad) * 30);
	int tileCoordY = tile(coordY + cos(angleRad) * 30);

	if ((buildingsMap1.getBuildingType(tileCoordX, tileCoordY)) == VOID_)	// Cheek_next_tile
	{
		coordX = coordX + sin(angleRad) * maxSpeed;
		coordY = coordY + cos(angleRad) * maxSpeed;
	}
	else	// find_path
	{
		findPath(buildingsMap1);
	}
	

	if (newTileCoordX != oldTileCoordX || newTileCoordY != oldTileCoordY)
	{
		destCoordX = mapMaxX * _HALF_TILE_;
		destCoordY = mapMaxY * _HALF_TILE_;
	}


	oldTileCoordX = newTileCoordX;
	oldTileCoordY = newTileCoordY;

	newTileCoordX = tile(coordX);
	newTileCoordY = tile(coordY);
}



void Entity::setDurability(int durability)
{
	this->durability = durability;
}

void Entity::setDamage(int damage)
{
	durability -= damage;
}


char Entity::getType() { return type; }
int Entity::getCoordX() { return int(coordX); }	
int Entity::getCoordY() { return int(coordY); }
int Entity::getAngleDeg() { return int(angleDeg); }
int Entity::getDurability() { return durability; }
int Entity::getEnemyMobsQuantity() { return enemyMobsQuantity; }


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
