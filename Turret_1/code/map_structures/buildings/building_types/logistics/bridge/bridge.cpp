
#include "bridge.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/resources/res_enum.h"


Bridge::Bridge(const uint16_t type, const char direction, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Building(type, durability, size, tile, team)
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
			if (BuildingsMap::canAccept(resType, aimTile))
			{
				wasteResorce(resType, 1);
				BuildingsMap::addToInventory(resType, aimTile);
			}
			return;
		}
	}
}


bool Bridge::canAccept(const uint16_t resType) const
{
	if (Building::isStorageFull(10))
		return false;
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
