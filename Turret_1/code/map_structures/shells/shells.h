#pragma once

#ifndef SHELLS_H
#define SHELLS_H

#include <iostream>
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>
#include <list>

#include "../buildings/buildings_map.h"



class Shell
{
	protected:
		
	char shellType;
	
	float angleRad;
	float angleDeg;
	
	float coordX;
	float coordY;
	
	float lineMotionX;
	float lineMotionY;
	
	int curentShellsLifeTime;
	int maxShellsLifeTime;
	
	bool isWasted;

	static inline sf::Image shellImage;
	static inline sf::Texture shellTexture;
	static inline sf::Sprite shellSprite;
	
	public:
		
		Shell(char v_shellType ,float v_coordX, float v_coordY, float v_angleRad, float v_angleDeg);

		static void prepareSprites();
		
		virtual void motion();

		virtual void explosion(BuildingsMap& buildingsMap1);
		
		virtual void drawShell(sf::RenderWindow& window, int time);

		virtual void tryPlayerShellsHitting(BuildingsMap& buildingsMap1);
		
		virtual void tryEnemyShellsHitting(BuildingsMap& buildingsMap1);
		
		float getCoordX();
		
		float getCoordY();
		
		bool getIsWasted();

		virtual ~Shell();
};


extern std::list<Shell*> playerShellsList;

extern std::list<Shell*> enemyShellsList;



void moveShellsList(int time);

void drawShellsList(sf::RenderWindow &window, int time);

void saveShellsList(int saveFileNumber);

void cleanShellsList();

void checkShellsHitting(BuildingsMap &buildingsMap1);




#endif // SHELLS_H
