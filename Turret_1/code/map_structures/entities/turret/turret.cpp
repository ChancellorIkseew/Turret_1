
#include <fstream>
#include <SFML\Graphics.hpp>

#include "turret.h"

#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"

#include "map_structures/team/team.h"

		
Turret::Turret(const int type, const TileCoord tile, Team* team)
{
	this->type = type;
	this->team = team;
	
	coord = t1::be::pixel(tile) ;
	
	angleDeg = 0;
	angleRad = 0;
	
	amooQuantity = 0;
	reloadTimer = 0;
	durability = 0;
}


void Turret::save(std::ofstream& fout) const
{
	fout << type << " " << durability << " " << int(angleDeg) << " " << amooQuantity << '\n';
}

void Turret::load(std::ifstream& fin)
{
	fin >> durability >> angleDeg >> amooQuantity;
}


PixelCoord Turret::findShootingAim() const
{
	for (auto& tm : Team::teams)
	{
		if (this->team->getID() != tm->getID())
		{
			for (auto entity = tm->entities.begin(); entity != tm->entities.end(); ++entity)
			{
				float deltaX = coord.x - (*entity)->getCoord().x;
				float deltaY = coord.y - (*entity)->getCoord().y;

				if (sqrt(deltaX * deltaX + deltaY * deltaY) < pixelRange)
				{
					return (*entity)->getCoord();
				}
			}
		}
	}

	TileCoord tile = t1::be::tile(coord);
	TileCoord aimTile{ 0, 0 };
	for (int i = 0; i < spyralRange; i++)
	{
		aimTile.x = tile.x + t1::be::coordSpyralArr[i].x;
		aimTile.y = tile.y + t1::be::coordSpyralArr[i].y;
		if (BuildingsMap::buildingExists(aimTile) && BuildingsMap::getTeamID(aimTile) != team->getID())
		{
			return t1::be::pixel(aimTile);
		}
	}
	
	return { 0.0f, 0.0f };
}

void Turret::reloadWeapon()
{
	if (reloadTimer > 0)
		--reloadTimer;
}


bool Turret::needAmoo() const
{
	if (amooQuantity < maxAmoo)
		return true;
	return false;
}

void Turret::setCoord(PixelCoord coord)
{
	this->coord = coord;
}

int Turret::getType() const { return type; }
TileCoord Turret::getTile() const { return t1::be::tile(coord); }
PixelCoord Turret::getCoord() const { return coord; }
int Turret::getAngleDeg() const {	return int(angleDeg); }
int Turret::getDurability() const { return durability; }
short Turret::getAmooQuantity() const { return amooQuantity; }


void Turret::prepareSprites()
{
	turretImage.loadFromFile("images/autocannon_turret.bmp");
	turretImage.createMaskFromColor(sf::Color(0, 255, 0));
	turretTexture.loadFromImage(turretImage);
	turretSprite.setTexture(turretTexture);
	turretSprite.setTextureRect(sf::IntRect(4, 5, 12, 20));
	turretSprite.setOrigin(6, 12);
}
