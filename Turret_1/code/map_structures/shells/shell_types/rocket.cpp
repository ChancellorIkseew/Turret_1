
#include <SFML\Graphics.hpp>

#include "rocket.h"

#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/particles/particles.h"


Rocket::Rocket(short type, PixelCoord coord, float angleRad, float angleDeg, Team* team) :
	Shell(type, coord, angleRad, angleDeg, team)
{
	damage = 0;
	float speed = 2.4f;
	maxLifeTime = 420;
	lineMotion.x = sin(angleRad) * speed;
	lineMotion.y = cos(angleRad) * speed;
}


void Rocket::tryShellsHitting()
{
	/*
	if (BuildingsMap::getBuildingType(t1::be::tile(coord)) != VOID_)
	{
		isWasted = true;
	}
	

	for (auto it = entitiesList.cbegin(); it != entitiesList.cend(); ++it)
	{
		if (abs((*it)->getCoord().x - coord.x) < 32 && abs((*it)->getCoord().y - coord.y) < 32) //Cheek distance_to_mob
		{
			isWasted = true;
			return;
		}
	}
	*/
}


void Rocket::explosion()
{
	/*
	for (auto it = entitiesList.begin(); it != entitiesList.end(); ++it)
	{
		int deltaX = coord.x - (*it)->getCoord().x;
		int deltaY = coord.y - (*it)->getCoord().y;

		if (sqrt(deltaX * deltaX + deltaY * deltaY) < 56) //Cheek distance_to_mob
		{
			(*it)->setDamage(20);
		}
	}
	*/

	BuildingsMap::setDamage(20, t1::be::tile(coord));
	particlesList.emplace_back(std::make_unique<Particle>(1, coord));
}


void Rocket::draw(sf::RenderWindow &window)
{
	if(curentLifeTime % 20 < 10)
		shellSprite.setTextureRect(sf::IntRect(5, 0, 10, 30));
	else
		shellSprite.setTextureRect(sf::IntRect(15, 0, 10, 30));
	
	shellSprite.setPosition(coord.x, coord.y);
	shellSprite.setRotation(angleDeg);
	window.draw(shellSprite);
}		
