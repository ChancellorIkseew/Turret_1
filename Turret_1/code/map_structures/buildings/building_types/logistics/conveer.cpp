
#include <iostream>
#include "conveer.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"

const TileCoord nullCoord = { 0, 0 };

Conveyer::Conveyer(char type, char direction, short durability, short size, const TileCoord tile, Team* team) : Building(type, durability, size, tile, team)
{
	this->direction = direction;
	timer = 5;
	speed = 2.0f;
}

Conveyer::~Conveyer()
{
	resUnits.clear();
}


void Conveyer::save(std::ofstream& fout) const
{
	fout << direction << '\n';
	Building::save(fout);
}

void Conveyer::load(std::ifstream& fin)
{
	fin >> direction;
	Building::load(fin);
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

	TileCoord cheekTile = { 0, 0 };

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
			if (res->coord.y <= -12 && !BuildingsMap::canAccept(*res, cheekTile))
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
				BuildingsMap::addToInventory(*res, cheekTile);
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
			if (res->coord.x <= -12 && !BuildingsMap::canAccept(*res, cheekTile))
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
				BuildingsMap::addToInventory(*res, cheekTile);
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
			if (res->coord.y >= 12 && !BuildingsMap::canAccept(*res, cheekTile))
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
				BuildingsMap::addToInventory(*res, cheekTile);
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
			if (res->coord.x >= 12 && !BuildingsMap::canAccept(*res, cheekTile))
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
				BuildingsMap::addToInventory(*res, cheekTile);
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
		return true;

	case 'a':
		for (auto& res : resUnits)
			if (res.coord.x >= 8)
				return false;
		return true;

	case 's':
		for (auto& res : resUnits)
			if (res.coord.y <= -8)
				return false;
		return true;

	case 'd':
		for (auto& res : resUnits)
			if (res.coord.x <= -8)
				return false;
		return true;
	}
	return false;
}


void Conveyer::draw(sf::RenderWindow& window)
{
	buildingSprite.setPosition(tile.x * _TILE_ + _HALF_TILE_, tile.y * _TILE_ + _HALF_TILE_);

	buildingSprite.setTextureRect(sf::IntRect(128, 96, 32, 32));
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

	for (auto& res : resUnits)
		res.draw(window, tile);
}



