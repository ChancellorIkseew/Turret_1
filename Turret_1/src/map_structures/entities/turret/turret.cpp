
#include "turret.h"

#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"

		
Turret::Turret(const TileCoord tile, Team* team) : team(team)
{
	coord = t1::be::pixel(tile) ;
}


void Turret::save(cereal::BinaryOutputArchive& archive) const
{
	int teamID = team->getID();
	archive(angleRad, amooQuantity, teamID);
}

void Turret::load(cereal::BinaryInputArchive& archive)
{
	int teamID;
	archive(angleRad, amooQuantity, teamID);
	angleDeg = t1::be::radToDegree(angleRad);
	team = world->getTeam(teamID);
}


void Turret::aim(const int spyralRange, const float pixelRange)
{
	aimCoord = Aiming::aimOnEntity(*this, pixelRange, *world);
}

void Turret::reloadWeapon()
{
	if (reloadTimer > 0)
		--reloadTimer;
}


bool Turret::needAmoo() const
{
	return amooQuantity < getMaxAmoo();
}

void Turret::setCoord(PixelCoord coord)
{
	this->coord = coord;
}


void Turret::prepareSprites()
{
	turretImage.loadFromFile("images/autocannon_turret.bmp");
	turretImage.createMaskFromColor(sf::Color(0, 255, 0));
	turretTexture.loadFromImage(turretImage);
	turretSprite.setTexture(turretTexture);
	turretSprite.setTextureRect(sf::IntRect(4, 5, 12, 20));
	turretSprite.setOrigin(6, 12);
}
