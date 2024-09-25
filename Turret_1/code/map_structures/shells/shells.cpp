
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>
#include <list>

#include "shells.h"

#include "shell_enum.h"
#include "map_structures/buildings/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/entities/entity.h"
#include "map_structures/entities/entities_util/entities_list.h"

		
Shell::Shell(int type ,float coordX, float coordY, float angleRad, float angleDeg)
{
	this->type = type;
	
	isWasted = false;
	
	this->coordX = coordX;
	this->coordY = coordY;
	
	this->angleRad = angleRad;
	this->angleDeg = angleDeg;
	
	float speed = 1.6f;
	lineMotionX = sin(angleRad)*speed;
	lineMotionY = cos(angleRad)*speed;
	
	maxLifeTime = 200;
	curentLifeTime = 0;
}


void Shell::prepareSprites()
{
	shellImage.loadFromFile("images/bullet.bmp");
	shellImage.createMaskFromColor(sf::Color(0, 255, 0));
	shellTexture.loadFromImage(shellImage);
	shellSprite.setTexture(shellTexture);
	shellSprite.setTextureRect(sf::IntRect(0, 0, 1, 2));
	shellSprite.setOrigin(1, 1);
}


void Shell::motion()
{
	coordX = coordX+lineMotionX;
	coordY = coordY+lineMotionY;
	
	++curentLifeTime;
	
	if(curentLifeTime > maxLifeTime)
	{
		isWasted = true;
	}
	
}


void Shell::explosion(BuildingsMap& buildingsMap1) { }


void Shell::draw(sf::RenderWindow &window, int time)
{
	shellSprite.setTextureRect(sf::IntRect(0, 0, 1, 2));
	shellSprite.setOrigin(0,1);
	shellSprite.setPosition(coordX, coordY);
	shellSprite.setRotation(angleDeg);
	window.draw(shellSprite);
}		


void Shell::tryEnemyShellsHitting(BuildingsMap &buildingsMap1)
{
	TileCoord tileCoord = tile(coordX, coordY);
	if(buildingsMap1.getBuildingType(tileCoord) != VOID_)
	{
		buildingsMap1.setDamage(1, tileCoord);
		isWasted = true;
	}
}


void Shell::tryPlayerShellsHitting(BuildingsMap& buildingsMap1)
{
	for (std::list<Entity*>::iterator it = entitiesList.begin(); it != entitiesList.end(); ++it)
	{
		if (abs((*it)->getCoord().x - coordX) < 7 && abs((*it)->getCoord().y - coordY) < 7)
		{
			(*it)->setDamage(1);
			isWasted = true;
			return;
		}
	}
}


float Shell::getCoordX() { return coordX; }

float Shell::getCoordY() { return coordY; }

bool Shell::getIsWasted() { return isWasted; }


std::list<Shell*> playerShellsList;		//Player's shels

std::list<Shell*> enemyShellsList;	//Enemie's shels


void moveShellsList(int time)
{
	for (std::list<Shell*>::iterator it = playerShellsList.begin(); it != playerShellsList.end(); ++it)
	{
		(*it)->motion();
	}
	
	for (std::list<Shell*>::iterator it = enemyShellsList.begin(); it != enemyShellsList.end(); ++it)
	{
		(*it)->motion();
	}
}


void checkShellsHitting(BuildingsMap& buildingsMap1)
{
	for (std::list<Shell*>::iterator it = playerShellsList.begin(); it != playerShellsList.end();)
	{

		(*it)->tryPlayerShellsHitting(buildingsMap1);

		if ((*it)->getIsWasted() == true)
		{
			(*it)->explosion(buildingsMap1);
			delete* it;
			it = playerShellsList.erase(it);
		}
		else
		{
			++it;
		}
	}

	for (std::list<Shell*>::iterator it = enemyShellsList.begin(); it != enemyShellsList.end();)
	{

		(*it)->tryEnemyShellsHitting(buildingsMap1);

		if ((*it)->getIsWasted() == true)
		{
			(*it)->explosion(buildingsMap1);
			delete* it;
			it = enemyShellsList.erase(it);
		}
		else
		{
			++it;
		}
	}
}


void drawShellsList(sf::RenderWindow& window, int time)
{
	for (std::list<Shell*>::iterator it = playerShellsList.begin(); it != playerShellsList.end(); ++it)
	{
		(*it)->draw(window, time);
		
	}
	
	for (std::list<Shell*>::iterator it = enemyShellsList.begin(); it != enemyShellsList.end(); ++it)
	{
		(*it)->draw(window, time);
	}
}


void loadShellsList(int saveFileNumber)
{
	
}


void saveShellsList(int saveFileNumber)
{
	
}


void cleanShellsList()
{
	playerShellsList.clear();
	enemyShellsList.clear();
}
