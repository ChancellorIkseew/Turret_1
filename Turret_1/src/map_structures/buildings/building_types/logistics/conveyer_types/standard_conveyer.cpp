
#include "standard_conveyer.h"


StandardConveyer::StandardConveyer(const char direction, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Conveyer(direction, durability, size, tile, team) { }


void StandardConveyer::draw(sf::RenderWindow& window)
{
	using namespace sf::Literals;
	buildingSprite.setPosition(sf::Vector2f(tile.x * _TILE_ + _HALF_TILE_, tile.y * _TILE_ + _HALF_TILE_));

	buildingSprite.setTextureRect(sf::IntRect({ 128, 96 }, X1_RECT));
	buildingSprite.setOrigin({ 16, 16 });

	switch (direction)
	{
	case 'a':
		buildingSprite.setRotation(270_deg);
		break;

	case 's':
		buildingSprite.setRotation(180_deg);
		break;

	case 'd':
		buildingSprite.setRotation(90_deg);
		break;
	}

	window.draw(buildingSprite);

	buildingSprite.setRotation(0_deg);
	buildingSprite.setOrigin({ 0, 0 });

	for (auto& res : resUnits)
		res.draw(window, tile);
}