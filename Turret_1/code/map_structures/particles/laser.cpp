
#include <iostream>
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>
#include <cmath>
#include <list>

#include "laser.h"
//#include "../shells.h"






	
	
		
LaserHandler::LaserHandler(int laserType)
{
	particlesLifeTime = 0;
}



LaserHandler::LaserHandler(int laserType ,float value_coordX, float value_coordY, float v_aimCoordX, float v_aimCoordY)
{
	isWasted = false;
	
	particlesLifeTime = 0;
	
	coordX = value_coordX;
	coordY = value_coordY;
	
	
	
	angleRad = atan2f(v_aimCoordX-coordX, v_aimCoordY-coordY);
	angleDeg = atan2f(v_aimCoordY-coordY, v_aimCoordX-coordX)*57.3f;
	
	
	lenghts = sqrt((v_aimCoordX-coordX)*(v_aimCoordX-coordX)+(v_aimCoordY-coordY)*(v_aimCoordY-coordY));
	if(lenghts > 128)
	{
		lenghts = 128;
	}
	
	
	std::cout << "particle created" << '\n';
}



void LaserHandler::Print()
{
	
}



void LaserHandler::motion()
{
	particlesLifeTime = particlesLifeTime + 1;
	
	
	if(particlesLifeTime > 40)
	{
		isWasted = true;
		
		std::cout << "particle wasted" << '\n';
	}
	
}

//void prepareTextures();

void LaserHandler::drawLaser(sf::RenderWindow &window, sf::Sprite &laserSprite, int time)
{
	laserSprite.setTextureRect(sf::IntRect(0, 0, lenghts, 3));
	laserSprite.setRotation(angleDeg);
	laserSprite.setPosition(coordX, coordY);
	window.draw(laserSprite);
	
	
}

//ParticlesHandler::void tryRocketsHitting(BuildingsMap &buildingsMap1);

//ParticlesHandler::bool isRocketsHitting(BuildingsMap &buildingsMap1);

float LaserHandler::getCoordX()
{
	return coordX;
}

float LaserHandler::getCoordY()
{
	return coordY;
}

bool LaserHandler::getIsWasted()
{
	return isWasted;
}

		
LaserHandler::~LaserHandler()
{
	
}



std::list<LaserHandler*> laserList;

//extern std::list<RocketsHandler*> enemyRocketsList;



void moveLaserList()
{
	for (std::list<LaserHandler*>::iterator it = laserList.begin(); it != laserList.end();)
	{
		if((*it)->getIsWasted() == true)
		{
			delete *it;
			it = laserList.erase(it);
		}
		else
		{
			(*it)->motion();
			++it;
		}
	}
}



void drawLaserList(sf::RenderWindow &window, sf::Sprite &laserSprite, int time)
{
	for (std::list<LaserHandler*>::iterator it = laserList.begin(); it != laserList.end(); ++it)
	{
		(*it)->drawLaser(window, laserSprite, time);
	}
}



void saveLaserList(int saveFileNumber)
{
	
}



void cleanLaserList()
{
	laserList.clear();
	/*
	for (std::list<LaserHandler*>::iterator it = laserList.begin(); it != laserList.end(); ++it)
	{
		delete *it;
		laserList.erase(it);
	}
	*/
}

//void checkEnemyRocketsHitting(BuildingsMap &buildingsMap1);





