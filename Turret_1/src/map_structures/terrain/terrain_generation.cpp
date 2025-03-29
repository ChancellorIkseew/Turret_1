
#include "terrain.h"

#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/terrain/terrain_enum.h"
#include "t1_system/random/t1_random.h"

using MapVector = std::vector<std::vector<std::unique_ptr<int>>>;
constexpr int DEFAULT_MAP_SIZE = 10000; // 100x100 tiles.

static inline bool tileExitst(const TileCoord tile, const TileCoord mapSize)
{
	return tile.x >= 0 && tile.x < mapSize.x && tile.y >= 0 && tile.y < mapSize.y;
}


inline int generateTile(const TerrainPre& terrainPre)
{
	for (auto& [type, frequency] : terrainPre.frequency)
	{
		if (frequency <= 0)
			continue;
		if (t1::Rand::getChance(DEFAULT_MAP_SIZE / frequency))
			return static_cast<int>(type);
	}
	return TILE_GROUND;
}


inline void generateSpot(const TerrainPre& terrainPre, MapVector& terrainMap, const TileCoord start)
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

		TileCoord nTile;
		for (int i = 0; i < 5; ++i)
		{
			nTile = tile + t1::be::coordSpyralArr[i];
			if (tileExitst(nTile, mapSize))
				*terrainMap[nTile.x][nTile.y] = static_cast<int>(tileType);
		}
	}
}


void TerrainMap::generate(const TerrainPre& terrainPre)
{
	t1::Rand::setSeed(terrainPre.seed);
	mapSize = terrainPre.mapSize;
	terrainMap.resize(mapSize.x);
	for (auto& x : terrainMap)
	{
		x.resize(mapSize.y);
		for (auto& y : x)
			y = std::make_unique<int>(TILE_GROUND);
	}

	for (int x = 0; x < mapSize.x; ++x)
	{
		for(int y = 0; y < mapSize.y; ++y)
		{ 
			int tileNewType = generateTile(terrainPre);
			if (tileNewType == TILE_GROUND)
				continue;
			*terrainMap[x][y] = tileNewType;
			generateSpot(terrainPre, terrainMap, TileCoord(x, y));
		}
	}

	// will_be_expanded
}
