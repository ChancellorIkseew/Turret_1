
#include <SFML\Graphics.hpp>

#include "rockets.h"

#include "map_structures/buildings/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/entities/entity.h"
#include "map_structures/entities/entities_util/entities_list.h"
#include "map_structures/particles/particles.h"


Rocket::Rocket(int type ,float coordX, float coordY, float angleRad, float angleDeg) : 
	Shell(type, coordX, coordY, angleRad, angleDeg)
{
	float speed = 2.4f;
	maxLifeTime = 420;
	lineMotionX = sin(angleRad) * speed;
	lineMotionY = cos(angleRad) * speed;
}


void Rocket::tryPlayerShellsHitting(BuildingsMap& buildingsMap1)
{
	for (std::list<Entity*>::iterator it = entitiesList.begin(); it != entitiesList.end(); ++it)
	{
		if (abs((*it)->getCoord().x - coordX) < 32 && abs((*it)->getCoord().y - coordY) < 32) //Cheek distance_to_mob
		{
			isWasted = true;
			return;
		}
	}
}


void Rocket::tryEnemyShellsHitting(BuildingsMap& buildingsMap1)
{
	if (buildingsMap1.getBuildingType(tile(coordX, coordY)) != VOID_)
	{
		isWasted = true;
	}
}


void Rocket::explosion(BuildingsMap& buildingsMap1)
{
	for (std::list<Entity*>::iterator it = entitiesList.begin(); it != entitiesList.end(); ++it)
	{
		int deltaX = coordX - (*it)->getCoord().x;
		int deltaY = coordY - (*it)->getCoord().y;

		if (sqrt(deltaX * deltaX + deltaY * deltaY) < 56) //Cheek distance_to_mob
		{
			(*it)->setDamage(20);
		}
	}

	buildingsMap1.setDamage(20, tile(coordX, coordY));
	particlesList.push_back(new Particle(1, coordX, coordY));
}


void Rocket::draw(sf::RenderWindow &window, int time)
{
	if(time%20 < 10)
	{
		shellSprite.setTextureRect(sf::IntRect(5, 0, 10, 30));
	}
	else
	{
		shellSprite.setTextureRect(sf::IntRect(15, 0, 10, 30));
	}
	
	shellSprite.setPosition(coordX, coordY);
	shellSprite.setRotation(angleDeg);
	window.draw(shellSprite);
}		
