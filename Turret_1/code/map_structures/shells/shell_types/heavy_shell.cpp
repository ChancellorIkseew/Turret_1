
#include <SFML\Graphics.hpp>

#include "heavy_shell.h"

#include "map_structures/buildings/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/entities/entity.h"
#include "map_structures/entities/entities_util/entities_list.h"
#include "map_structures/particles/particles.h"


HeavyShell::HeavyShell(int type, float coordX, float coordY, float angleRad, float angleDeg) :
	Shell(type, coordX, coordY, angleRad, angleDeg)
{
	float speed = 1.6f;
	maxLifeTime = 500;
	lineMotionX = sin(angleRad) * speed;
	lineMotionY = cos(angleRad) * speed;
}


void HeavyShell::tryPlayerShellsHitting(BuildingsMap& buildingsMap1)
{
	for (std::list<Entity*>::iterator it = entitiesList.begin(); it != entitiesList.end(); ++it)	//Cheek distance_to_mob
	{
		if (abs((*it)->getCoord().x - coordX) < 7 && abs((*it)->getCoord().y - coordY) < 7)
		{
			(*it)->setDamage(20);
			isWasted = true;
			return;
		}
	}
}


void HeavyShell::tryEnemyShellsHitting(BuildingsMap& buildingsMap1)
{
	TileCoord tileCoord = tile(coordX, coordY);

	if (buildingsMap1.getBuildingType(tileCoord) != VOID_)
	{
		buildingsMap1.setDamage(20, tileCoord);
		isWasted = true;
	}
}


void HeavyShell::explosion(BuildingsMap& buildingsMap1)
{
	for (std::list<Entity*>::iterator it = entitiesList.begin(); it != entitiesList.end(); ++it)	//Cheek damage
	{
		int deltaX = coordX - (*it)->getCoord().x;
		int deltaY = coordY - (*it)->getCoord().y;


		if (sqrt(deltaX * deltaX + deltaY * deltaY) < 48)
		{
			(*it)->setDamage(10);
		}
	}

	buildingsMap1.setDamage(20, tile(coordX, coordY));

	//particlesList.push_back(new Particle(1, coordX, coordY));
}


void HeavyShell::draw(sf::RenderWindow& window, int time)
{
	shellSprite.setTextureRect(sf::IntRect(2, 0, 3, 7));
	shellSprite.setOrigin(2, 1);
	shellSprite.setPosition(coordX, coordY);
	shellSprite.setRotation(angleDeg);
	window.draw(shellSprite);
}
