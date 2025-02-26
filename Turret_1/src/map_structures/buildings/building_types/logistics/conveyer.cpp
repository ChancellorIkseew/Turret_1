
#include <iostream>
#include <cereal/types/vector.hpp>
#include "conveyer.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/world/world.h"

const TileCoord nullCoord = { 0, 0 };

Conveyer::Conveyer(const char direction, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Building(durability, size, tile, team)
{
	this->direction = direction;
}


void Conveyer::save(cereal::BinaryOutputArchive& archive) const
{
	Building::save(archive);
	archive(direction, resUnits);
}

void Conveyer::load(cereal::BinaryInputArchive& archive)
{
	Building::load(archive);
	archive(direction, resUnits);
}


void Conveyer::addToInventory(ResourceUnit& unit)
{
	resUnits.emplace_back(std::move(unit));
}


void Conveyer::interact()
{
	if (--timer > 0)
		return;
	timer = 5;

	TileCoord cheekTile;
	BuildingsMap& buildingsMap = world->getBuildingsMap();
	const float speed = getTransmitionSpeed();

	for (auto res = resUnits.begin(); res != resUnits.end();)
	{
		switch (res->direction)
		{
		case 'w':
			if (direction != res->direction && res->coord.y <= speed)
			{
				res->coord.y = 0;
				res->direction = direction;
				goto retW;
			}

			cheekTile = { tile.x, tile.y - 1 };
			if (res->coord.y <= -12 && !buildingsMap.canAccept(*res, cheekTile))
				goto retW;

			for (auto& it : resUnits)
			{
				if ((res->coord.y > it.coord.y && res->coord.y - it.coord.y <= 10 && abs(it.coord.x) <= 5) ||
					(it.direction == 's' && abs(it.coord.y) <= 8 && abs(res->coord.y) > 8))
					goto retW;
			}

			res->coord.y -= speed;

			if (res->coord.y <= -_HALF_TILE_)
			{
				res->coord.y += _TILE_;
				buildingsMap.addToInventory(*res, cheekTile);
				res = resUnits.erase(res);
				break;
			}
			
			retW:
			++res;
			break;

		case 'a':
			if (direction != res->direction && res->coord.x <= speed)
			{
				res->coord.x = 0;
				res->direction = direction;
				goto retA;
			}

			cheekTile = { tile.x - 1, tile.y };
			if (res->coord.x <= -12 && !buildingsMap.canAccept(*res, cheekTile))
				goto retA;

			for (auto& it : resUnits)
			{
				if ((res->coord.x > it.coord.x && res->coord.x - it.coord.x <= 10 && abs(it.coord.y) <= 5) ||
					(it.direction == 'd' && abs(it.coord.x) <= 8 && abs(res->coord.x) > 8))
					goto retA;
			}

			res->coord.x -= speed;

			if (res->coord.x <= -_HALF_TILE_)
			{
				res->coord.x += _TILE_;
				buildingsMap.addToInventory(*res, cheekTile);
				res = resUnits.erase(res);
				break;
			}

			retA:
			++res;
			break;

		case 's':
			if (direction != res->direction && res->coord.y >= -speed)
			{
				res->coord.y = 0;
				res->direction = direction;
				goto retS;
			}

			cheekTile = { tile.x, tile.y + 1 };
			if (res->coord.y >= 12 && !buildingsMap.canAccept(*res, cheekTile))
				goto retS;

			for (auto& it : resUnits)
			{
				if ((res->coord.y < it.coord.y && res->coord.y - it.coord.y >= -10 && abs(it.coord.x) <= 5) ||
					(it.direction == 'w' && abs(it.coord.y) <= 8 && abs(res->coord.y) > 8))
					goto retS;
			}

			res->coord.y += speed;

			if (res->coord.y >= _HALF_TILE_)
			{
				res->coord.y -= _TILE_;
				buildingsMap.addToInventory(*res, cheekTile);
				res = resUnits.erase(res);
				break;
			}

			retS:
			++res;
			break;

		case 'd':
			if (direction != res->direction && res->coord.x >= -speed)
			{
				res->coord.x = 0;
				res->direction = direction;
				goto retD;
			}

			cheekTile = { tile.x + 1, tile.y };
			if (res->coord.x >= 12 && !buildingsMap.canAccept(*res, cheekTile))
				goto retD;

			for (auto& it : resUnits)
			{
				if ((res->coord.x < it.coord.x && res->coord.x - it.coord.x >= -10 && abs(it.coord.y) <= 5) ||
					(it.direction == 'a' && abs(it.coord.x) <= 8 && abs(res->coord.x) > 8))
					goto retD;
			}

			res->coord.x += speed;

			if (res->coord.x >= _HALF_TILE_)
			{
				res->coord.x -= _TILE_;
				buildingsMap.addToInventory(*res, cheekTile);
				res = resUnits.erase(res);
				break;
			}

			retD:
			++res;
			break;
		}
	}
}


bool Conveyer::canAccept(const ResourceUnit& unit) const
{
	switch (unit.direction)
	{
	case 'w':
		for (auto& res : resUnits)
			if (res.coord.y >= 8)
				return false;
		break;
	case 'a':
		for (auto& res : resUnits)
			if (res.coord.x >= 8)
				return false;
		break;
	case 's':
		for (auto& res : resUnits)
			if (res.coord.y <= -8)
				return false;
		break;
	case 'd':
		for (auto& res : resUnits)
			if (res.coord.x <= -8)
				return false;
		break;
	}
	return true;
}
