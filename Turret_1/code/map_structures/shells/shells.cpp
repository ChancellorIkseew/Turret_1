
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>
#include <list>

#include "shells.h"

#include "map_structures/buildings/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"

#include "map_structures/entities/entities.h"
#include "map_structures/entities/entities_util/entities_list.h"

		
Shell::Shell(char v_shellType ,float v_coordX, float v_coordY, float v_angleRad, float v_angleDeg)
{
	shellType = v_shellType;
	
	isWasted = false;
	
	coordX = v_coordX; //+ sin(angleRad)*8;
	coordY = v_coordY; //+ cos(angleRad)*8;
	
	angleRad = v_angleRad;
	angleDeg = v_angleDeg;
	
	float speed = 0;

	switch (shellType)
	{
		case '1':
			speed = 1.6f;
			maxShellsLifeTime = 200;	// basic_shell
			break;
		case '2':
			speed = 1.6f;
			maxShellsLifeTime = 500;	// explosive_shell
			break;

		case '3':
			speed = 2.4f;
			maxShellsLifeTime = 420;	// rocket
			break;

		case '4':
			speed = 3.6f;
			maxShellsLifeTime = 400;	// rail_bolt
			break;

		case '5':
			speed = 1.2f;
			maxShellsLifeTime = 100;	// gravity_pulse
			break;

		case '6':
			speed = 0.8f;
			maxShellsLifeTime = 120;	// flame
			break;

		case '7':
			speed = 13.8f;
			maxShellsLifeTime = 40;		// laser
			break;

		default:
			speed = 0;
			maxShellsLifeTime = 0;		// error_defence
			break;
	}

	lineMotionX = sin(angleRad)*speed;
	lineMotionY = cos(angleRad)*speed;
	
	curentShellsLifeTime = 0;
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
	
	++curentShellsLifeTime;
	
	if(curentShellsLifeTime > maxShellsLifeTime)
	{
		isWasted = true;
	}
	
}


void Shell::explosion(BuildingsMap& buildingsMap1) { }


void Shell::draw(sf::RenderWindow &window, int time)
{
	if(shellType == '1')
	{
		shellSprite.setTextureRect(sf::IntRect(0, 0, 1, 2));
		shellSprite.setOrigin(0,1);
	}
	else
	{
		shellSprite.setTextureRect(sf::IntRect(2, 0, 3, 7));
		shellSprite.setOrigin(2,1);
	}
	
	shellSprite.setPosition(coordX, coordY);
	shellSprite.setRotation(angleDeg);
	window.draw(shellSprite);
}		


void Shell::tryEnemyShellsHitting(BuildingsMap &buildingsMap1)
{
	int tileCoordX = tile(coordX);
	int tileCoordY = tile(coordY);
	
	if(buildingsMap1.getBuildingType(tileCoordX, tileCoordY) != VOID_)
	{
		if(shellType == '1')
		{
			buildingsMap1.setDamage(1, tileCoordX, tileCoordY);
		}
		else
		{
			buildingsMap1.setDamage(20, tileCoordX, tileCoordY);
		}
		
		isWasted = true;
	}
	
}


void Shell::tryPlayerShellsHitting(BuildingsMap& buildingsMap1)
{
	for (std::list<Entity*>::iterator it = entitiesList.begin(); it != entitiesList.end(); ++it)
	{
		if (abs((*it)->getCoordX() - coordX) < 7 && abs((*it)->getCoordY() - coordY) < 7)
		{
			(*it)->setDamage(10);
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
