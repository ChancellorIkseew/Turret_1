#pragma once

#ifndef LASER_H
#define LASER_H

#include <iostream>
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>
#include <list>

//#include "../buildings.h"
//#include "../shells.h"



class LaserHandler
{
	private:
		
	bool isFriendly;
	
	float angleRad;
	float angleDeg;
	
	float coordX;
	float coordY;
	
	int lenghts;
	
	float lineMotionX;
	float lineMotionY;
	
	int particlesLifeTime;
	
	bool isWasted;
	
	
	public:
		
		LaserHandler(int rocketType);
		
		LaserHandler(int rocketType ,float value_coordX, float value_coordY, float value_aimCoordX, float value_aimCoordY);
		
		void Print();
		
		void motion();
		
		//void prepareTextures();
		
		void drawLaser(sf::RenderWindow &window, sf::Sprite &laserSprite, int time);
		
		//void tryRocketsHitting(BuildingsMap &buildingsMap1);
		
		//bool isRocketsHitting(BuildingsMap &buildingsMap1);
		
		float getCoordX();
		
		float getCoordY();
		
		bool getIsWasted();

		
		~LaserHandler();
};


extern std::list<LaserHandler*> laserList;


void moveLaserList();

void drawLaserList(sf::RenderWindow &window, sf::Sprite &shellSprite, int time);

void saveLaserList(int saveFileNumber);

void cleanLaserList();

//void checkEnemyRocketsHitting(BuildingsMap &buildingsMap1);




#endif // LASER_H
