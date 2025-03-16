
#include "rocket.h"

#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/shells/damage/damage.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"

constexpr int EXP_RADIUS = 3; // radius in tiles
constexpr float ACTIVATION_RADIUS = static_cast<float>(_TILE_);
constexpr float EXP_DAMAGE = 20.0f;
constexpr float SPEED = 2.4f;
constexpr uint16_t MAX_LIFI_TIME = 420;

Rocket::Rocket(const PixelCoord coord, const float angleRad, Team* team) :
	Shell(coord, angleRad, team)
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
	
	for (auto& [teamID, team] : world->getTeams())
	{
		if (this->team->getID() != teamID)
		{
			for (auto& entity : team->getEneities().getList())
			{
				if (!t1::be::areCloser(coord, entity->getCoord(), ACTIVATION_RADIUS))
					continue;
				isWasted = true;
				return;
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
	using namespace sf::Literals;
	if(restLifeTime % 20 < 10)
		shellSprite.setTextureRect(sf::IntRect({ 5, 0 }, { 10, 30 }));
	else
		shellSprite.setTextureRect(sf::IntRect({ 15, 0 }, { 10, 30 }));
	
	shellSprite.setOrigin({ 7, 1 });
	shellSprite.setPosition({ coord.x, coord.y });
	shellSprite.setRotation(sf::radians(PI - angleRad));
	window.draw(shellSprite);
}		
