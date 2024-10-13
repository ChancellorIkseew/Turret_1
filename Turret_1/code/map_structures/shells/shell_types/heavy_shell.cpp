
#include <SFML\Graphics.hpp>

#include "heavy_shell.h"

#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/particles/particles.h"


HeavyShell::HeavyShell(short type, PixelCoord coord, float angleRad, float angleDeg, Team* team) :
	Shell(type, coord, angleRad, angleDeg, team)
{
	damage = 20;
	float speed = 1.6f;
	maxLifeTime = 500;
	lineMotion.x = sin(angleRad) * speed;
	lineMotion.y = cos(angleRad) * speed;
}


void HeavyShell::explosion()
{
	/*
	for (auto it = entitiesList.begin(); it != entitiesList.end(); ++it)
	{
		int deltaX = coord.x - (*it)->getCoord().x;
		int deltaY = coord.y - (*it)->getCoord().y;

		if (sqrt(deltaX * deltaX + deltaY * deltaY) < 48)
		{
			(*it)->setDamage(10);
		}
	}

	BuildingsMap::setDamage(20, t1::be::tile(coord));
	*/
	//particlesList.push_back(std::make_unique<Particle>(1, coord));
}


void HeavyShell::draw(sf::RenderWindow& window)
{
	shellSprite.setTextureRect(sf::IntRect(2, 0, 3, 7));
	shellSprite.setOrigin(2, 1);
	shellSprite.setPosition(coord.x, coord.y);
	shellSprite.setRotation(angleDeg);
	window.draw(shellSprite);
}
