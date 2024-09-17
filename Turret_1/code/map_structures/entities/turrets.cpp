
#include <iostream>
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>
#include <cmath>
#include <list>


#include "turrets.h"

#include "entities.h"
#include "entities_util/entities_list.h"

#include "../shells/shells.h"
#include "../shells/shell_types/rockets.h"

#include "../buildings/building/buildings_enum.h"

#include "turret_types/autocannon_turret.h"
#include "turret_types/rocket_turret.h"

		
Turret::Turret(char v_turretType ,int tileX, int tileY, float curentAngle, short curentDurability)
{
	this->set0();
	turretType = v_turretType;
	
	coordX = tileX * _TILE_ + _HALF_TILE_;
	coordY = tileY * _TILE_ + _HALF_TILE_;
	
	
	aimCoordX = 0;
	aimCoordY = 0;
	
	angleDeg = curentAngle;
	
	
	durability = curentDurability;
	amooQuant = 0;
	activity = true;

	reloadTimer = 0;

	pixelRange = 0;
}

Turret::Turret()
{
	this->set0();
}

Turret::~Turret()
{

}


void Turret::save(std::ofstream& fout)
{
	fout << turretType << " " << durability << " " << int(angleDeg) << " " << amooQuant << '\n';
}

void Turret::load(std::ifstream& fin)
{
	fin >> durability >> angleDeg >> amooQuant;
}


bool Turret::findAim()
{
	for (std::list<Entity*>::iterator it = entitiesList.begin(); it != entitiesList.end(); ++it)
	{
		int deltaX = coordX - (*it)->getCoordX();
		int deltaY = coordY - (*it)->getCoordY();

		float angleRad = atan2f(deltaX, deltaY);

		if (sqrt(deltaX * deltaX + deltaY * deltaY) < pixelRange)
		{
			aimCoordX = (*it)->getCoordX();
			aimCoordY = (*it)->getCoordY();

			//std::cout << "angle: " << angleRad << " deltaX: " << deltaX << '\n';
			return true;
			break;
		}
	}
	return false;
}

		
void Turret::shooting()
{

}
		


void Turret::setCoord(int v_coordX, int v_coordY)
{
	coordX = v_coordX;
	coordY = v_coordY;
}



int Turret::getType()
{
	return turretType;
}

int Turret::getTileCoordX()
{
	return (coordX-8)/16;
}

int Turret::getTileCoordY()
{
	return (coordY-8)/16;
}

int Turret::getCoordX()
{
	return coordX;
}

int Turret::getCoordY()
{
	return coordY;
}

int Turret::getAngleDeg()
{
	return int(angleDeg);
}
	
int Turret::getAimCoordX()
{
	return int(aimCoordX);
}

int Turret::getAimCoordY()
{
	return int(aimCoordY);
}

int Turret::getDurability()
{
	return durability;
}
 	
short Turret::getAmooQuant()
{
	return amooQuant;
}

int Turret::getAmooType() { return 0; }

char Turret::getActivity()
{
	char a;
	
	if(activity)
	{
		a = '1';
	}
	else
	{
		a = '0';
	}
	
	return a;
}



void Turret::set0()
{
	turretType = 0;

	coordX = 0;
	coordY = 0;

	angleRad = 0;
	angleDeg = 0;

	aimCoordX = 0;
	aimCoordY = 0;


	durability = 0;
	amooQuant = 0;
	maxAmoo = 0;
	activity = 0;

	reloadTimer = 0;

	pixelRange = 0;
}


bool Turret::needAmoo() { return false; }
void Turret::takeAmoo(int resType) { }



Turret* Turret::setTurret(int turretType, int tileX, int tileY)
{
	switch (turretType)
	{
	case AUTOCANNON_TURRET:
		return new AutocannonTurret(AUTOCANNON_TURRET, tileX, tileY, 0, 0);

	case ROCKET_TURRET:
		return new RocketTurret(ROCKET_TURRET, tileX, tileY, 0, 0);

	}
}



void Turret::prepareSprites()
{
	turretImage.loadFromFile("images/autocannon_turret.bmp");
	turretImage.createMaskFromColor(sf::Color(0, 255, 0));
	turretTexture.loadFromImage(turretImage);
	turretSprite.setTexture(turretTexture);
	turretSprite.setTextureRect(sf::IntRect(4, 5, 12, 20));
	turretSprite.setOrigin(6, 12);
}

void Turret::draw(sf::RenderWindow& window) { }
