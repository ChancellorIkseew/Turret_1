#pragma once
#ifndef PRE_SETTINGS
#define PRE_SETTINGS

#include <string>
#include <map>

#include "map_structures/entities/entity/entity.h"
#include "map_structures/base_engine/tile_coord.h"

#include "pre_settings/general_pre.h"
#include "pre_settings/terrain_pre.h"


class PreSettings
{

private:

	static inline std::string saveFileName = "0";

	// terrain:
	static inline TileCoord mapSize = { 0, 0 };
	static inline short generationMetodth = 0;
	static inline int worldSeed = 0;

	// buildings:
	static inline float buildingsMaxDurabilityModidier = 1.0f;
	static inline float buildingExpansesMidifier = 1.0f;
	static inline float buildingsConstructionSpeedModifier = 1.0f;

	// enemy_mobs:
	static inline int enemyMobQuantityModifier = 1;
	static inline float enemyMobMaxDurabilityModifier = 1.0f;
	static inline int enemyMobVirtIntLevel = 0;
	//std::string enemyMobSpawnConfiguration;

	// shells:
	//float playerShellsDamageModifier, enemyShellsDamageModifier;
	//float plaerExplodiveDamageModifier, enemyExplosiveDamageModifier;

	// wave_timer:
	//int firstWaveWaitTime;
	//int standardWaveWaitTime;
	//int bossWaveWaitTime;

	// technologies_tree:
	//bool areAllTechnologiesAvaluable;

	static inline GeneralPre general;
	static inline TerrainPre terrain;

public:

	PreSettings(std::string saveFolderName);
	~PreSettings() = default;

	static void loadPreSettings();
	static void savePreSettings();

	// terrain:
	static TileCoord getMapSize();
	static short getGenerationMetodth();
	static int getWorldSeed();

	static void setMapSize(const TileCoord mapSize);
	static void setGenerationMetod(const short metodth);
	static void setWorldSeed(const int seed);

	// buildings
	static float getBuildingsMaxDurabilityModidier();
	static float getBuildingExpansesMidifier();
	static float getBuildingsConstructionSpeedModifier();

	static void setBuildingsMaxDurabilityModidier(float value);
	static void setBuildingExpansesMidifier(float value);
	static void setBuildingsConstructionSpeedModifier(float value);

	static void setStartBalance(std::map<int, int> startRes);

	friend void Entity::initPreSettings();
	
	static GeneralPre getGeneral() { return general; }
	static TerrainPre getTerrain() { return terrain; }

};


#endif // PRE_SETTINGS
