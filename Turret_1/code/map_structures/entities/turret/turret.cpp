
#include <fstream>
#include <SFML\Graphics.hpp>

#include "turret.h"

#include "map_structures/buildings/building/buildings_enum.h"

		
Turret::Turret(const int type, const TileCoord tile)
{
	this->type = type;
	
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
	/*
	for (auto it = entitiesList.cbegin(); it != entitiesList.cend(); ++it)
	{
		float deltaX = coord.x - (*it)->getCoord().x;
		float deltaY = coord.y - (*it)->getCoord().y;

		float angleRad = atan2f(deltaX, deltaY);

		if (sqrt(deltaX * deltaX + deltaY * deltaY) < pixelRange)
		{
			return (*it)->getCoord();
		}
	}
	*/
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
