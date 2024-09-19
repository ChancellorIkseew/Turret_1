
#include <SFML\Graphics.hpp>

#include "rockets.h"

#include "map_structures/buildings/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/entities/entities.h"
#include "map_structures/entities/entities_util/entities_list.h"
#include "map_structures/particles/particles.h"


Rocket::Rocket(char v_shellType ,float v_coordX, float v_coordY, float v_angleRad, float v_angleDeg) : 
	Shell(v_shellType, v_coordX, v_coordY, v_angleRad, v_angleDeg)
{

}


void Rocket::tryPlayerShellsHitting(BuildingsMap& buildingsMap1)
{
	for (std::list<Entity*>::iterator it = entitiesList.begin(); it != entitiesList.end(); ++it)	//Cheek distance_to_mob
	{
		if (abs((*it)->getCoordX() - coordX) < 32 && abs((*it)->getCoordY() - coordY) < 32)
		{
			std::cout << "player missle activated" << '\n';
			isWasted = true;
			//this->explosion(buildingsMap1);
			return;
		}
	}
}


void Rocket::tryEnemyShellsHitting(BuildingsMap& buildingsMap1)
{
	if (buildingsMap1.getBuildingType(tile(coordX), tile(coordY)) != VOID_)
	{
		std::cout << "enemy missle activated" << '\n';
		isWasted = true;
		//this->explosion(buildingsMap1);
	}
}


void Rocket::explosion(BuildingsMap& buildingsMap1)
{
	for (std::list<Entity*>::iterator it = entitiesList.begin(); it != entitiesList.end(); ++it)	//Cheek damage
	{
		int deltaX = coordX - (*it)->getCoordX();
		int deltaY = coordY - (*it)->getCoordY();


		if (sqrt(deltaX * deltaX + deltaY * deltaY) < 56)
		{
			(*it)->setDamage(200);

			std::cout << "missle damage registred" << '\n';
		}

	}

	buildingsMap1.setDamage(20, tile(coordX), tile(coordY));

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
	
	//std::cout << "rocket draw works" << '\n';
}		
