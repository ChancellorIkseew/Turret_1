
#include "small_drill.h"
#include "map_structures/world/world.h"

constexpr int STORAGE_CAPACITY = 5;

SmallDrill::SmallDrill(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Drill(durability, size, tile, team) { }


void SmallDrill::interact()
{
	if (timer % 15 == 0)
		Building::placeResourceUnitX1(findResource(), world->getBuildingsMap());

	if (timer == 0)
	{
		timer = 150;
		Drill::mineResource(1, STORAGE_CAPACITY);
	}

	this->animation();
	--timer;
}


void SmallDrill::animation()
{
	if (isStorageFull(STORAGE_CAPACITY))
		return;
	rotorAngle += 0.5f;
	if (rotorAngle >= 360.0f)
		rotorAngle -= 360.0f;
}

void SmallDrill::draw(sf::RenderWindow& window)
{
	buildingSprite.setOrigin(16, 16);
	buildingSprite.setRotation(rotorAngle);
	buildingSprite.setPosition(tile.x * _TILE_ + _HALF_TILE_, tile.y * _TILE_ + _HALF_TILE_);
	buildingSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	window.draw(buildingSprite);

	buildingSprite.setOrigin(0, 0);
	buildingSprite.setRotation(0);
	buildingSprite.setPosition(tile.x * _TILE_, tile.y * _TILE_);
	buildingSprite.setTextureRect(sf::IntRect(32, 0, 32, 32));

	window.draw(buildingSprite);
}
