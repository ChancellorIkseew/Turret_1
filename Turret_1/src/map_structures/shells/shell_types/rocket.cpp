
#include "rocket.h"

#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/shells/damage/damage.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"

constexpr int ACTIVATION_RADIUS = _TILE_;
constexpr int EXP_RADIUS = 3; // radius in tiles
constexpr float EXP_DAMAGE = 20.0f;
constexpr float SPEED = 2.4f;
constexpr uint16_t MAX_LIFI_TIME = 420;

Rocket::Rocket(PixelCoord coord, float angleRad, float angleDeg, Team* const team) :
	Shell(coord, angleRad, angleDeg, team)
{
	// Rocket has no colision damage. Only burst damage. That's why there is not sth like "damage = x".
	restLifeTime = MAX_LIFI_TIME;
	lineMotion.x = sin(angleRad) * SPEED;
	lineMotion.y = cos(angleRad) * SPEED;
}


void Rocket::tryHitting()
{
	TileCoord tile = t1::be::tile(coord);
	BuildingsMap& buildingsMap = world->getBuildingsMap();
	if (!buildingsMap.isVoidBuilding(tile) && buildingsMap.getTeamID(tile) != team->getID())
	{
		isWasted = true;
		return;
	}
	
	for (auto& it : world->getTeams())
	{
		Team& team = *it.second;
		if (this->team->getID() != team.getID())
		{
			for (auto& entity : team.getEneities().getList())
			{
				float deltaX = coord.x - entity->getCoord().x;
				float deltaY = coord.y - entity->getCoord().y;
				if (abs(deltaX) < ACTIVATION_RADIUS && abs(deltaY) < ACTIVATION_RADIUS)
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
	Damage::createExplosion(coord, EXP_RADIUS, EXP_DAMAGE, 0.25f, *world);
	world->getParticles().spawnParticle(2, coord);
}


void Rocket::draw(sf::RenderWindow &window)
{
	if(restLifeTime % 20 < 10)
		shellSprite.setTextureRect(sf::IntRect(5, 0, 10, 30));
	else
		shellSprite.setTextureRect(sf::IntRect(15, 0, 10, 30));
	
	shellSprite.setOrigin(7, 1);
	shellSprite.setPosition(coord.x, coord.y);
	shellSprite.setRotation(angleDeg);
	window.draw(shellSprite);
}		
