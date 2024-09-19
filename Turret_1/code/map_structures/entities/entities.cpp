
#include <iostream>
#include <fstream>
#include <SFML\Graphics.hpp>

#include "entities.h"
#include "mob_enum.h"
#include "map_structures/buildings/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/pre-settings/pre-settings.h"


int Entity::enemyMobsQuantity = 0;


void Entity::initPreSettings()
{
	mapMaxX = PreSettings::getMapMaxX();
	mapMaxY = PreSettings::getMapMaxY();
}

Entity::Entity(int v_entityType)		//1st spawn
{
	entityType = v_entityType;
	
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

Entity::Entity(int v_entityType ,float v_coordX, float v_coordY, float curentAngleDeg, short curentDurability)
{
	entityType = v_entityType;
	coordX = v_coordX;
	coordY = v_coordY;
	angleDeg = curentAngleDeg;
	durability = curentDurability;
	
	std::cout << "sucsessfull entity load" << '\n';
}

Entity::~Entity()
{
	
}


void Entity::save(std::ofstream& fout)
{
	fout << entityType << " " << coordX << " " << coordY << " " << angleDeg << " " << durability << '\n';
	fout << "$\n";
}

void Entity::load(std::ifstream& fin)
{
	fin >> coordX >> coordY >> angleDeg >> durability;
	char specialSymbol;
	fin >> specialSymbol;
}


void Entity::motion(BuildingsMap &buildingsMap1, int time, float maxSpeed)
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



void Entity::setDurability(int v_durability)
{
	durability = v_durability;
}

void Entity::setDamage(int damage)
{
	durability = durability - damage;
}


char Entity::getEntityType() { return entityType; }
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
