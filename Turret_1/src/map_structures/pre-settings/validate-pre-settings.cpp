
#include "pre-settings.h"
#include "t1_system/random/t1_random.h"
#include <algorithm>

constexpr int MIN_MAP_SIZE = 20, MAX_MAP_SIZE = 5000;

void PreSettings::validate(PreSettings& preSettings)
{
	TerrainPre& terrain = preSettings.changeTerrain();
	terrain.mapSize.x = std::clamp(terrain.mapSize.x, MIN_MAP_SIZE, MAX_MAP_SIZE);
	terrain.mapSize.y = std::clamp(terrain.mapSize.y, MIN_MAP_SIZE, MAX_MAP_SIZE);
	if (terrain.seed == 0)
		terrain.seed = t1::Rand::getValue(0, 1000000);
}
