
#include "bridge.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/world/world.h"

constexpr int STORAGE_CAPACITY = 10;

Bridge::Bridge(const char direction, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Building(durability, size, tile, team)
{
	this->direction = direction;
}


void Bridge::save(cereal::BinaryOutputArchive& archive) const
{
	Building::save(archive);
	archive(direction);
}

void Bridge::load(cereal::BinaryInputArchive& archive)
{
	Building::load(archive);
	archive(direction);
}


void Bridge::interact()
{
	transmitResourceUnit();
}


void Bridge::transmitResourceUnit()
{
	ResType resType = findResource();
	if (resType == ResType::NO_RESOURCES)
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

		BuildingsMap& buildingsMap = world->getBuildingsMap();
		if (buildingsMap.getBuildingType(aimTile) != BuildingType::ROUTER)
			continue;

		if (buildingsMap.canAccept(resType, aimTile))
		{
			wasteResorce(resType, 1);
			buildingsMap.addToInventory(resType, aimTile);
		}

		return;
	}
}


bool Bridge::canAccept(const ResType resType) const
{
	return !Building::isStorageFull(STORAGE_CAPACITY);
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
