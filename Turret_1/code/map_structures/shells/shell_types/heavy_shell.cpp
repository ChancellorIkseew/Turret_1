
#include <SFML\Graphics.hpp>

#include "heavy_shell.h"

#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/particles/particles.h"
#include "map_structures/team/team.h"


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
	TileCoord tile = t1::be::tile(coord);
	for (int i = 0; i < 9; ++i)
	{
		tile.x += t1::be::coordSpyralArr[i].x;
		tile.y += t1::be::coordSpyralArr[i].y;
		if (!BuildingsMap::isVoidBuilding(tile))
		{
			BuildingsMap::setDamage(10, tile);
		}
	}

	for (auto it = Team::teams.begin(); it != Team::teams.end(); ++it)
	{
		for (auto entity = (*it)->entities.begin(); entity != (*it)->entities.end(); ++entity)
		{
			float deltaX = coord.x - (*entity)->getCoord().x;
			float deltaY = coord.y - (*entity)->getCoord().y;
			float deltaS = sqrt(deltaX * deltaX + deltaY * deltaY);
			if (deltaS < 48)
			{
				(*entity)->setDamage(10);
			}
		}
	}
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
