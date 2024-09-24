
#include "bridge.h"
#include "map_structures/buildings/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/resources/resource_units.h"
#include "map_structures/resources/res_enum.h"


Bridge::Bridge(int type, char direction, short durability, short size, const TileCoord tile) : Building(type, durability, size, tile)
{
	this->direction = direction;
}

Bridge::Bridge() : Building()
{
	type = BRIDGE;
}


void Bridge::save(std::ofstream& fout) const
{
	fout << type << " " << size << " " << durability <<
		" " << tile.x << " " << tile.y << " " << direction << '\n';

	for (auto it = storedResourcesList.cbegin(); it != storedResourcesList.cend(); ++it)
	{
		//fout << (*it)->type << " " << (*it)->quant << '\n';
	}

	fout << "$\n";
}



void Bridge::load(std::ifstream& fin)
{
	fin >> size >> durability >> tile.x >> tile.y >> direction;

	while (true)
	{
		char nextSymbol;
		fin >> nextSymbol;

		if (nextSymbol == '$')
		{
			break;
		}

		fin.seekg(-1, std::ios::cur);
		int resType;
		fin >> resType;
		short amount;
		fin >> amount;
		storedResourcesList.push_back(StoredResource{ resType, amount });
	}
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
	short comonResQuant = 0;

	for (auto it = storedResourcesList.cbegin(); it != storedResourcesList.cend(); ++it)
	{
		comonResQuant = comonResQuant + it->quant;

	}

	if (comonResQuant < 11)
	{
		return true;
	}
	return false;
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
