
#include "standard_conveyer.h"
#include "map_structures/world/world.h"


StandardConveyer::StandardConveyer(const char direction, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Conveyer(direction, durability, size, tile, team) { }

constexpr sf::Vector2i start(128, 96);
constexpr sf::Vector2i tileY(0, _TILE_);

constexpr sf::IntRect downUp(start, X1_RECT);
constexpr sf::IntRect downUpLeft(start + tileY, X1_RECT);
constexpr sf::IntRect downUpRight(start + tileY * 2, X1_RECT);
constexpr sf::IntRect allSides(start + tileY * 3, X1_RECT);
constexpr sf::IntRect leftUp(start + tileY * 4, X1_RECT);
constexpr sf::IntRect rightUp(start + tileY * 5, X1_RECT);
constexpr sf::IntRect leftRightUp(start + tileY * 6, X1_RECT);


static bool checkTile(int x, int y) {
	return false;
}


void StandardConveyer::draw(sf::RenderWindow& window)
{
	using namespace sf::Literals;
	buildingSprite.setPosition(sf::Vector2f(tile.x * _TILE_ + _HALF_TILE_, tile.y * _TILE_ + _HALF_TILE_));
	buildingSprite.setOrigin({ 16, 16 });
	BuildingsMap& map = world->getBuildingsMap();

	switch (direction)
	{
	case 'w':
		if (map.getBuildingDirection(TileCoord(tile.x, tile.y + 1)) == 'w')
		{
			if (map.getBuildingDirection(TileCoord(tile.x + 1, tile.y)) == 'a')
				if (map.getBuildingDirection(TileCoord(tile.x - 1, tile.y)) == 'd')
					buildingSprite.setTextureRect(allSides);
				else
					buildingSprite.setTextureRect(downUpRight);
			else
				if (map.getBuildingDirection(TileCoord(tile.x - 1, tile.y)) == 'd')
					buildingSprite.setTextureRect(downUpLeft);
				else
					buildingSprite.setTextureRect(downUp);	//Conveyer W
		}
		else
		{
			if (map.getBuildingDirection(TileCoord(tile.x + 1, tile.y)) == 'a')
				if (map.getBuildingDirection(TileCoord(tile.x - 1, tile.y)) == 'd')
					buildingSprite.setTextureRect(leftRightUp);
				else
					buildingSprite.setTextureRect(rightUp);
			else
				if (map.getBuildingDirection(TileCoord(tile.x - 1, tile.y)) == 'd')
					buildingSprite.setTextureRect(leftUp);
				else
					buildingSprite.setTextureRect(downUp);	//Conveyer W
		}
		break;

	case 'a':
		if (map.getBuildingDirection(TileCoord(tile.x + 1, tile.y)) == 'a')
		{
			if (map.getBuildingDirection(TileCoord(tile.x, tile.y - 1)) == 's')
				if (map.getBuildingDirection(TileCoord(tile.x, tile.y + 1)) == 'w')
					buildingSprite.setTextureRect(allSides);
				else
					buildingSprite.setTextureRect(downUpRight);
			else
				if (map.getBuildingDirection(TileCoord(tile.x, tile.y + 1)) == 'w')
					buildingSprite.setTextureRect(downUpLeft);
				else
					buildingSprite.setTextureRect(downUp);	//Conveyer W
		}
		else
		{
			if (map.getBuildingDirection(TileCoord(tile.x, tile.y - 1)) == 's')
				if (map.getBuildingDirection(TileCoord(tile.x, tile.y + 1)) == 'w')
					buildingSprite.setTextureRect(leftRightUp);
				else
					buildingSprite.setTextureRect(rightUp);
			else
				if (map.getBuildingDirection(TileCoord(tile.x, tile.y + 1)) == 'w')
					buildingSprite.setTextureRect(leftUp);
				else
					buildingSprite.setTextureRect(downUp);	//Conveyer W
		}
		buildingSprite.setRotation(270_deg);
		break;

	case 's':
		if (map.getBuildingDirection(TileCoord(tile.x, tile.y - 1)) == 's')
		{
			if (map.getBuildingDirection(TileCoord(tile.x - 1, tile.y)) == 'd')
				if (map.getBuildingDirection(TileCoord(tile.x + 1, tile.y)) == 'a')
					buildingSprite.setTextureRect(allSides);
				else
					buildingSprite.setTextureRect(downUpRight);
			else
				if (map.getBuildingDirection(TileCoord(tile.x + 1, tile.y)) == 'a')
					buildingSprite.setTextureRect(downUpLeft);
				else
					buildingSprite.setTextureRect(downUp);	//Conveyer W
		}
		else
		{
			if (map.getBuildingDirection(TileCoord(tile.x - 1, tile.y)) == 'd')
				if (map.getBuildingDirection(TileCoord(tile.x + 1, tile.y)) == 'a')
					buildingSprite.setTextureRect(leftRightUp);
				else
					buildingSprite.setTextureRect(rightUp);
			else
				if (map.getBuildingDirection(TileCoord(tile.x + 1, tile.y)) == 'a')
					buildingSprite.setTextureRect(leftUp);
				else
					buildingSprite.setTextureRect(downUp);	//Conveyer W
		}
		buildingSprite.setRotation(180_deg);
		break;

	case 'd':
		if (map.getBuildingDirection(TileCoord(tile.x - 1, tile.y)) == 'd')
		{
			if (map.getBuildingDirection(TileCoord(tile.x, tile.y + 1)) == 'w')
				if (map.getBuildingDirection(TileCoord(tile.x, tile.y - 1)) == 's')
					buildingSprite.setTextureRect(allSides);
				else
					buildingSprite.setTextureRect(downUpRight);
			else
				if (map.getBuildingDirection(TileCoord(tile.x, tile.y - 1)) == 's')
					buildingSprite.setTextureRect(downUpLeft);
				else
					buildingSprite.setTextureRect(downUp);	//Conveyer W
		}
		else
		{
			if (map.getBuildingDirection(TileCoord(tile.x, tile.y + 1)) == 'w')
				if (map.getBuildingDirection(TileCoord(tile.x, tile.y - 1)) == 's')
					buildingSprite.setTextureRect(leftRightUp);
				else
					buildingSprite.setTextureRect(rightUp);
			else
				if (map.getBuildingDirection(TileCoord(tile.x, tile.y - 1)) == 's')
					buildingSprite.setTextureRect(leftUp);
				else
					buildingSprite.setTextureRect(downUp);	//Conveyer W
		}
		buildingSprite.setRotation(90_deg);
		break;
	}

	window.draw(buildingSprite);

	buildingSprite.setRotation(0_deg);
	buildingSprite.setOrigin({ 0, 0 });

	for (auto& res : resUnits)
		res.draw(window, tile);
}