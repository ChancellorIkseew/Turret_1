
#include "big_drill.h"
#include "map_structures/world/world.h"

constexpr int STORAGE_CAPACITY = 20;

BigDrill::BigDrill(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Drill(durability, size, tile, team) { }


void BigDrill::interact()
{
	if (timer % 15 == 0)
		Building::placeResourceUnitX4(findResource(), world->getBuildingsMap());

	if (timer == 0)
	{
		timer = 150;
		Drill::mineResource(2, STORAGE_CAPACITY);
	}

	this->animation();
	--timer;
}

void BigDrill::animation()
{
	if (isStorageFull(STORAGE_CAPACITY))
		return;
	rotorAngle += 0.5f;
	if (rotorAngle >= 360.0f)
		rotorAngle -= 360.0f;
}

void BigDrill::draw(sf::RenderWindow& window)
{
	using namespace sf::Literals;
	buildingSprite.setOrigin({ 32, 32 });
	buildingSprite.setRotation(sf::degrees(rotorAngle));
	buildingSprite.setPosition(sf::Vector2f(tile.x * _TILE_ + _TILE_, tile.y * _TILE_ + _TILE_));
	buildingSprite.setTextureRect(sf::IntRect({ 0, 32 }, X2_RECT));

	window.draw(buildingSprite);

	buildingSprite.setOrigin({ 0, 0 });
	buildingSprite.setRotation(0_deg);
	buildingSprite.setPosition(sf::Vector2f(tile.x * _TILE_, tile.y * _TILE_));
	buildingSprite.setTextureRect(sf::IntRect({ 64, 32 }, X2_RECT));

	window.draw(buildingSprite);
}
