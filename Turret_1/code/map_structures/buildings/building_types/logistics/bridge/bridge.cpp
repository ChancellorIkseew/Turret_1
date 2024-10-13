
#include "bridge.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/resources/resource_units.h"
#include "map_structures/resources/res_enum.h"


Bridge::Bridge(int type, char direction, short durability, short size, const TileCoord tile, Team* team) : Building(type, durability, size, tile, team)
{
	this->direction = direction;
}


void Bridge::save(std::ofstream& fout) const
{
	fout << direction << '\n';
	Building::save(fout);
}

void Bridge::load(std::ifstream& fin)
{
	fin >> direction;
	Building::load(fin);
}


void Bridge::interact()
{
	transmitResourceUnit();
}


void Bridge::transmitResourceUnit()
{
	int resType = findResource();
	if (resType == RES_NO_RESOURCES)
		return;

	TileCoord aimTile{ tile.x, tile.y };

	for (int i = 0; i < 5; ++i)
	{
		switch (direction)
		{
		case 'w':
			--aimTile.y;
			break;
		case 'a':
			--aimTile.x;
			break;
		case 's':
			++aimTile.y;
			break;
		case 'd':
			++aimTile.x;
			break;
		}

		if (BuildingsMap::getBuildingType(aimTile) == ROUTER)
		{
			if (BuildingsMap::isThisPositionFree(aimTile, 0))
			{
				wasteResorce(resType, 1);
				BuildingsMap::addToInventory(resType, aimTile);
			}
			return;
		}
	}
}



bool Bridge::isThisPositionFree(int position) const
{
	if (Building::isStorageFull(10))
		return false;
	return true;
}

bool Bridge::canAccept(int resType) const
{
	return true;
}


void Bridge::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tile.x * _TILE_ + _HALF_TILE_, tile.y * _TILE_ + _HALF_TILE_);
	buildingSprite.setTextureRect(sf::IntRect(0, 224, 32, 32));
	buildingSprite.setOrigin(16, 16);

	switch (direction)
	{
	case 'a':
		buildingSprite.setRotation(270);
		break;

	case 's':
		buildingSprite.setRotation(180);
		break;

	case 'd':
		buildingSprite.setRotation(90);
		break;
	}

	window.draw(buildingSprite);

	buildingSprite.setRotation(0);
	buildingSprite.setOrigin(0, 0);
}
