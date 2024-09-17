
#include "bridge.h"

#include "../../../../buildings_map.h"
#include "../../../buildings_enum.h"
#include "../../../../../resources/resource_units.h"


Bridge::Bridge(int v_type, char v_direction, short v_durability, short v_size, int tileX, int tileY) : Building(v_type, v_durability, v_size, tileX, tileY)
{
	direction = v_direction;
}

Bridge::Bridge() : Building()
{
	type = BRIDGE;
}


void Bridge::save(std::ofstream& fout)
{
	fout << type << " " << size << " " << durability <<
		" " << tileX << " " << tileY << " " << direction << '\n';

	for (std::list<StoredResource>::iterator it = storedResourcesList.begin(); it != storedResourcesList.end(); ++it)
	{
		//fout << (*it)->type << " " << (*it)->quant << '\n';
	}

	fout << "$\n";
}



void Bridge::load(std::ifstream& fin)
{
	fin >> size >> durability >> tileX >> tileY >> direction;

	while (true)
	{
		char resType;
		fin >> resType;

		if (resType != '$')
		{
			short amount;
			fin >> amount;
			storedResourcesList.emplace_back(StoredResource{ resType, amount });
		}
		else
		{
			break;
		}
	}
}


void Bridge::interact()
{
	placeResourceUnit('X');
}


void Bridge::placeResourceUnit(int type)
{
	short comonResQuant = 0;

	for (std::list<StoredResource>::iterator it = storedResourcesList.begin(); it != storedResourcesList.end(); ++it)
	{
		comonResQuant = comonResQuant + it->quant;
		if (it->quant != 0)
			type = it->type;
	}

	int aimTileX = tileX;
	int aimTileY = tileY;

	if(comonResQuant > 0)
	for (int i = 0; i < 5; ++i)
	{
		switch (direction)
		{
		case 'w':
			--aimTileY;
			break;
		case 'a':
			--aimTileX;
			break;
		case 's':
			++aimTileY;
			break;
		case 'd':
			++aimTileX;
			break;
		}

		if (BuildingsMap::getBuildingType(aimTileX, aimTileY) == ROUTER)
		{
			if (BuildingsMap::isThisPositionFree(aimTileX, aimTileY, 0))
			{
				wasteResorce(type, 1);
				BuildingsMap::addToInventory(type, aimTileX, aimTileY);
			}
			return;
		}
	}
}



bool Bridge::isThisPositionFree(int position)
{
	short comonResQuant = 0;

	for (std::list<StoredResource>::iterator it = storedResourcesList.begin(); it != storedResourcesList.end(); ++it)
	{
		comonResQuant = comonResQuant + it->quant;

	}

	if (comonResQuant < 11)
	{
		return true;
	}
	return false;
}



bool Bridge::canAccept(int resType)
{
	return true;
}


void Bridge::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tileX * _TILE_ + _HALF_TILE_, tileY * _TILE_ + _HALF_TILE_);
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


Bridge::~Bridge()
{

}
