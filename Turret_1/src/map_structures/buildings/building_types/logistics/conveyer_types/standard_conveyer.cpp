
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


static inline bool checkTile(const BuildingsMap& map, int x, int y) {
	const BuildingType type = map.getBuildingType(TileCoord(x, y));
	return type >= BuildingType::ROUTER && type <= BuildingType::RAIL_BOLT_FACTORY;
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
		if (map.getBuildingDirection(TileCoord(tile.x, tile.y + 1)) == 'w' || checkTile(map, tile.x, tile.y + 1))
		{
			if (map.getBuildingDirection(TileCoord(tile.x + 1, tile.y)) == 'a' || checkTile(map, tile.x + 1, tile.y))
				if (map.getBuildingDirection(TileCoord(tile.x - 1, tile.y)) == 'd' || checkTile(map, tile.x - 1, tile.y))
					buildingSprite.setTextureRect(allSides);
				else
					buildingSprite.setTextureRect(downUpRight);
			else
				if (map.getBuildingDirection(TileCoord(tile.x - 1, tile.y)) == 'd' || checkTile(map, tile.x - 1, tile.y))
					buildingSprite.setTextureRect(downUpLeft);
				else
					buildingSprite.setTextureRect(downUp);	//Conveyer W
		}
		else
		{
			if (map.getBuildingDirection(TileCoord(tile.x + 1, tile.y)) == 'a' || checkTile(map, tile.x + 1, tile.y))
				if (map.getBuildingDirection(TileCoord(tile.x - 1, tile.y)) == 'd' || checkTile(map, tile.x - 1, tile.y))
					buildingSprite.setTextureRect(leftRightUp);
				else
					buildingSprite.setTextureRect(rightUp);
			else
				if (map.getBuildingDirection(TileCoord(tile.x - 1, tile.y)) == 'd' || checkTile(map, tile.x - 1, tile.y))
					buildingSprite.setTextureRect(leftUp);
				else
					buildingSprite.setTextureRect(downUp);	//Conveyer W
		}
		break;

	case 'a':
		if (map.getBuildingDirection(TileCoord(tile.x + 1, tile.y)) == 'a' || checkTile(map, tile.x + 1, tile.y))
		{
			if (map.getBuildingDirection(TileCoord(tile.x, tile.y - 1)) == 's' || checkTile(map, tile.x, tile.y - 1))
				if (map.getBuildingDirection(TileCoord(tile.x, tile.y + 1)) == 'w' || checkTile(map, tile.x, tile.y + 1))
					buildingSprite.setTextureRect(allSides);
				else
					buildingSprite.setTextureRect(downUpRight);
			else
				if (map.getBuildingDirection(TileCoord(tile.x, tile.y + 1)) == 'w' || checkTile(map, tile.x, tile.y + 1))
					buildingSprite.setTextureRect(downUpLeft);
				else
					buildingSprite.setTextureRect(downUp);	//Conveyer W
		}
		else
		{
			if (map.getBuildingDirection(TileCoord(tile.x, tile.y - 1)) == 's' || checkTile(map, tile.x, tile.y - 1))
				if (map.getBuildingDirection(TileCoord(tile.x, tile.y + 1)) == 'w' || checkTile(map, tile.x, tile.y + 1))
					buildingSprite.setTextureRect(leftRightUp);
				else
					buildingSprite.setTextureRect(rightUp);
			else
				if (map.getBuildingDirection(TileCoord(tile.x, tile.y + 1)) == 'w' || checkTile(map, tile.x, tile.y + 1))
					buildingSprite.setTextureRect(leftUp);
				else
					buildingSprite.setTextureRect(downUp);	//Conveyer W
		}
		buildingSprite.setRotation(270_deg);
		break;

	case 's':
		if (map.getBuildingDirection(TileCoord(tile.x, tile.y - 1)) == 's' || checkTile(map, tile.x, tile.y - 1))
		{
			if (map.getBuildingDirection(TileCoord(tile.x - 1, tile.y)) == 'd' || checkTile(map, tile.x - 1, tile.y))
				if (map.getBuildingDirection(TileCoord(tile.x + 1, tile.y)) == 'a' || checkTile(map, tile.x + 1, tile.y))
					buildingSprite.setTextureRect(allSides);
				else
					buildingSprite.setTextureRect(downUpRight);
			else
				if (map.getBuildingDirection(TileCoord(tile.x + 1, tile.y)) == 'a' || checkTile(map, tile.x + 1, tile.y))
					buildingSprite.setTextureRect(downUpLeft);
				else
					buildingSprite.setTextureRect(downUp);	//Conveyer W
		}
		else
		{
			if (map.getBuildingDirection(TileCoord(tile.x - 1, tile.y)) == 'd' || checkTile(map, tile.x - 1, tile.y))
				if (map.getBuildingDirection(TileCoord(tile.x + 1, tile.y)) == 'a' || checkTile(map, tile.x + 1, tile.y))
					buildingSprite.setTextureRect(leftRightUp);
				else
					buildingSprite.setTextureRect(rightUp);
			else
				if (map.getBuildingDirection(TileCoord(tile.x + 1, tile.y)) == 'a' || checkTile(map, tile.x + 1, tile.y))
					buildingSprite.setTextureRect(leftUp);
				else
					buildingSprite.setTextureRect(downUp);	//Conveyer W
		}
		buildingSprite.setRotation(180_deg);
		break;

	case 'd':
		if (map.getBuildingDirection(TileCoord(tile.x - 1, tile.y)) == 'd' || checkTile(map, tile.x - 1, tile.y))
		{
			if (map.getBuildingDirection(TileCoord(tile.x, tile.y + 1)) == 'w' || checkTile(map, tile.x, tile.y + 1))
				if (map.getBuildingDirection(TileCoord(tile.x, tile.y - 1)) == 's' || checkTile(map, tile.x, tile.y - 1))
					buildingSprite.setTextureRect(allSides);
				else
					buildingSprite.setTextureRect(downUpRight);
			else
				if (map.getBuildingDirection(TileCoord(tile.x, tile.y - 1)) == 's' || checkTile(map, tile.x, tile.y - 1))
					buildingSprite.setTextureRect(downUpLeft);
				else
					buildingSprite.setTextureRect(downUp);	//Conveyer W
		}
		else
		{
			if (map.getBuildingDirection(TileCoord(tile.x, tile.y + 1)) == 'w' || checkTile(map, tile.x, tile.y + 1))
				if (map.getBuildingDirection(TileCoord(tile.x, tile.y - 1)) == 's' || checkTile(map, tile.x, tile.y - 1))
					buildingSprite.setTextureRect(leftRightUp);
				else
					buildingSprite.setTextureRect(rightUp);
			else
				if (map.getBuildingDirection(TileCoord(tile.x, tile.y - 1)) == 's' || checkTile(map, tile.x, tile.y - 1))
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
}