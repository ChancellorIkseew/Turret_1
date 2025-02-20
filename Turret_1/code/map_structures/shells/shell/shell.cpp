
#include "shell.h"

#include "shell_enum.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"


Shell::Shell(const PixelCoord coord, float angleRad, float angleDeg, Team* const team)
{
	this->coord = coord;
	this->angleRad = angleRad;
	this->angleDeg = angleDeg;
	this->team = team;
	
	damage = 1;
	float speed = 1.6f;
	lineMotion.x = sin(angleRad)*speed;
	lineMotion.y = cos(angleRad)*speed;
	
	maxLifeTime = 200;
	curentLifeTime = 0;
}

void Shell::save(cereal::BinaryOutputArchive& archive) const
{
	archive(coord);
	archive(lineMotion);
	archive(angleRad);
	archive(damage);
	archive(curentLifeTime);
	archive(maxLifeTime);
}

void Shell::load(cereal::BinaryInputArchive& archive)
{
	archive(coord);
	archive(lineMotion);
	archive(angleRad);
	angleDeg = t1::be::radToDegree(angleRad);
	archive(damage);
	archive(curentLifeTime);
	archive(maxLifeTime);
}


void Shell::motion()
{
	coord.x += lineMotion.x;
	coord.y += lineMotion.y;
	
	if(++curentLifeTime > maxLifeTime)
		isWasted = true;
}

void Shell::explosion() { }

void Shell::tryHitting()
{
	
	TileCoord tile = t1::be::tile(coord);
	BuildingsMap& buildingsMap = world->getBuildingsMap();
	if (!buildingsMap.isVoidBuilding(tile) && buildingsMap.getTeamID(tile) != team->getID())
	{
		buildingsMap.setDamage(this->damage, tile);
		isWasted = true;
	}

	for (auto& team : world->getTeams())
	{
		if (this->team->getID() != team.first)
		{
			for (auto& entity : team.second->getEneities().getList())
			{
				if (abs(entity->getCoord().x - coord.x) < 7 && abs(entity->getCoord().y - coord.y) < 7)
				{
					entity->setDamage(this->damage);
					isWasted = true;
					return;
				}
			}
		}
	}
}


PixelCoord Shell::getCoord() { return coord; }
bool Shell::getIsWasted() { return isWasted; }


void Shell::prepareSprites()
{
	shellImage.loadFromFile("images/bullet.bmp");
	shellImage.createMaskFromColor(sf::Color(0, 255, 0));
	shellTexture.loadFromImage(shellImage);
	shellSprite.setTexture(shellTexture);
	shellSprite.setTextureRect(sf::IntRect(0, 0, 1, 2));
	shellSprite.setOrigin(1, 1);
}

void Shell::draw(sf::RenderWindow& window)
{
	shellSprite.setTextureRect(sf::IntRect(0, 0, 1, 2));
	shellSprite.setOrigin(0, 1);
	shellSprite.setPosition(coord.x, coord.y);
	shellSprite.setRotation(angleDeg);
	window.draw(shellSprite);
}
