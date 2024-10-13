
#include <SFML\Graphics.hpp>

#include "rocket.h"

#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/particles/particles.h"
#include "map_structures/team/team.h"


Rocket::Rocket(short type, PixelCoord coord, float angleRad, float angleDeg, Team* team) :
	Shell(type, coord, angleRad, angleDeg, team)
{
	damage = 0; // only_burst_damage
	float speed = 2.4f;
	maxLifeTime = 420;
	lineMotion.x = sin(angleRad) * speed;
	lineMotion.y = cos(angleRad) * speed;
}


void Rocket::tryHitting()
{
	TileCoord tile = t1::be::tile(coord);
	if (!BuildingsMap::isVoidBuilding(tile) && BuildingsMap::getTeamID(tile) != team->getID())
	{
		isWasted = true;
		return;
	}
	
	for (auto it = Team::teams.begin(); it != Team::teams.end(); ++it)
	{
		if (this->team->getID() != (*it)->getID())
		{
			for (auto entity = (*it)->entities.begin(); entity != (*it)->entities.end(); ++entity)
			{
				float deltaX = coord.x - (*entity)->getCoord().x;
				float deltaY = coord.y - (*entity)->getCoord().y;
				if (abs(deltaX) < 32 && abs(deltaY) < 32)
				{
					isWasted = true;
					return;
				}
			}
		}
	}
}


void Rocket::explosion()
{
	TileCoord tile = t1::be::tile(coord);
	for (int i = 0; i < 9; ++i)
	{
		tile.x += t1::be::coordSpyralArr[i].x;
		tile.y += t1::be::coordSpyralArr[i].y;
		if (!BuildingsMap::isVoidBuilding(tile))
		{
			BuildingsMap::setDamage(20, tile);
		}
	}

	for (auto it = Team::teams.begin(); it != Team::teams.end(); ++it)
	{
		for (auto entity = (*it)->entities.begin(); entity != (*it)->entities.end(); ++entity)
		{
			float deltaX = coord.x - (*entity)->getCoord().x;
			float deltaY = coord.y - (*entity)->getCoord().y;
			float deltaS = sqrt(deltaX * deltaX + deltaY * deltaY);
			if (deltaS < 56)
			{
				(*entity)->setDamage(20);
			}
		}	
	}

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
