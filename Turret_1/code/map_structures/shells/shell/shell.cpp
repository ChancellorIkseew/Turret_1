
#include <SFML\Graphics.hpp>

#include "shell.h"

#include "shell_enum.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"


Shell::Shell(short type, const PixelCoord coord, float angleRad, float angleDeg)
{
	this->type = type;
	this->coord = coord;
	this->angleRad = angleRad;
	this->angleDeg = angleDeg;
	
	damage = 1;
	float speed = 1.6f;
	lineMotion.x = sin(angleRad)*speed;
	lineMotion.y = cos(angleRad)*speed;
	
	maxLifeTime = 200;
	curentLifeTime = 0;
	isWasted = false;
}


void Shell::motion()
{
	coord.x += lineMotion.x;
	coord.y += lineMotion.y;
	
	if(++curentLifeTime > maxLifeTime)
		isWasted = true;
}

void Shell::explosion() { }

void Shell::tryEnemyShellsHitting()
{
	TileCoord tileCoord = t1::be::tile(coord);
	if(BuildingsMap::getBuildingType(tileCoord) != VOID_)
	{
		BuildingsMap::setDamage(this->damage, tileCoord);
		isWasted = true;
	}
}

void Shell::tryPlayerShellsHitting()
{
	/*
	for (auto it = entitiesList.begin(); it != entitiesList.end(); ++it)
	{
		if (abs((*it)->getCoord().x - coord.x) < 7 && abs((*it)->getCoord().y - coord.y) < 7)
		{
			(*it)->setDamage(this->damage);
			isWasted = true;
			return;
		}
	}
	*/
}

void Shell::tryShellsHitting()
{

}


PixelCoord Shell::getCoord() { return coord; }
bool Shell::getIsWasted() { return isWasted; }


void Shell::prepareSprites()
{
	shellImage.loadFromFile("images/bullet.bmp");
	shellImage.createMaskFromColor(sf::Color(0, 255, 0));
	shellTexture.loadFromImage(shellImage);
	shellSprite.setTexture(shellTexture);
	shellSprite.setTextureRect(sf::IntRect(0, 0, 1, 2));
	shellSprite.setOrigin(1, 1);
}

void Shell::draw(sf::RenderWindow& window)
{
	shellSprite.setTextureRect(sf::IntRect(0, 0, 1, 2));
	shellSprite.setOrigin(0, 1);
	shellSprite.setPosition(coord.x, coord.y);
	shellSprite.setRotation(angleDeg);
	window.draw(shellSprite);
}
