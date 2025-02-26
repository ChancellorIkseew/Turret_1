
#include "router.h"
#include "map_structures/resources/res_enum.h"
#include "map_structures/world/world.h"

constexpr int STORAGE_CAPACITY = 10;

Router::Router(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Building(durability, size, tile, team) { }


void Router::interact()
{
	ResType resType = findResource();
	if (resType != ResType::NO_RESOURCES)
		placeResourceUnitX1(resType, world->getBuildingsMap());
}


bool Router::canAccept(const ResType resType) const
{
	return !Building::isStorageFull(STORAGE_CAPACITY);
}


void Router::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tile.x * _TILE_, tile.y * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(0, 256, 32, 32));
	window.draw(buildingSprite);
}
