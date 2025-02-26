
#include <memory>
#include <limits>

#include "terrain_generator.h"

#include "map_structures/base_engine/base_engine.h"
#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/terrain/terrain_enum.h"
#include "t1_system/random/t1_random.h"

static inline bool tileExitst(const TileCoord tile, const TileCoord mapSize)
{
	return tile.x >= 0 && tile.x < mapSize.x && tile.y >= 0 && tile.y < mapSize.y;
}

inline int generateTile(TerrainPre& terrainPre);
inline void generateSpot(const TerrainPre& terrainPre, std::vector<std::vector<std::unique_ptr<int>>>& terrainMap, const TileCoord start);

std::vector<std::vector<std::unique_ptr<int>>> generateTerrain(TerrainPre& terrainPre)
{
	if (terrainPre.seed == 0)
		terrainPre.seed = t1::Rand::getValue(0, 1000000);
	t1::Rand::setSeed(terrainPre.seed);

	std::vector<std::vector<std::unique_ptr<int>>> terrainMap;
	const TileCoord mapSize = terrainPre.mapSize;

	terrainMap.resize(mapSize.x);
	terrainMap.reserve(mapSize.x);
	for (auto& x : terrainMap)
	{
		x.resize(mapSize.y);
		x.reserve(mapSize.y);
		for (auto& y : x)
		{
			y = std::make_unique<int>(TILE_GROUND);
		}
	}

	for (int x = 0; x < mapSize.x; ++x)
	{
		for(int y = 0; y < mapSize.y; ++y)
		{ 
			int tileNewType = generateTile(terrainPre);
			if (tileNewType != TILE_GROUND)
			{
				*terrainMap[x][y] = tileNewType;
				generateSpot(terrainPre, terrainMap, { x, y });
			}
		}
	}

	// will_be_expanded

	return terrainMap;
}


inline int generateTile(TerrainPre& terrainPre)
{
	for (auto& it : terrainPre.frequency)
	{
		if (it.second > 0)
		{
			int flag = t1::Rand::getValue(0, (10000 / it.second));
			if (flag == 0)
				return static_cast<int>(it.first);
		}
	}
	return TILE_GROUND;
}


inline void generateSpot(const TerrainPre& terrainPre, std::vector<std::vector<std::unique_ptr<int>>>& terrainMap, const TileCoord start)
{
	const TileCoord mapSize = terrainPre.mapSize;

	ResType tileType = static_cast<ResType>(*terrainMap[start.x][start.y]);
	int spotSize = static_cast<int>(terrainPre.depositSize.find(tileType)->second);

	TileCoord tile = start;
	
	for (int s = 0; s < spotSize; ++s)
	{
		if (s != 0)
		{
			int dir = t1::Rand::getValue(0, 3);
			if (dir == 3)
				tile.x -= 1;
			else if (dir == 2)
				tile.y -= 1;
			else if (dir == 1)
				tile.x += 1;
			else if (dir == 0)
				tile.y += 1;
		}
			
		TileCoord nTile = { 0, 0 };
		for (int i = 0; i < 5; ++i)
		{
			nTile.x = tile.x + t1::be::coordSpyralArr[i].x;
			nTile.y = tile.y + t1::be::coordSpyralArr[i].y;
			if (tileExitst(nTile, mapSize))
				*terrainMap[nTile.x][nTile.y] = static_cast<int>(tileType);
		}
	}
}
