#pragma once
#ifndef PRE_SETTINGS
#define PRE_SETTINGS

#include <string>




class PreSettings
{

private:

	static inline std::string saveFileName = "0";

	// terrain:
	static inline int mapMaxX = 0, mapMaxY = 0;
	static inline short generationMetodth = 0;
	static inline int worldSeed = 0;

	// buildings:
	static inline float buildingsMaxDurabilityModidier = 1;
	static inline float buildingExpansesMidifier = 1;
	static inline float buildingsConstructionSpeedModifier = 1;

	// enemy_mobs:
	//float enemyMobMaxDurabilityModifier;
	//short enemyMobVirtIntLevel;
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

public:

	PreSettings(std::string saveFolderName);

	static void loadPreSettings();

	static void savePreSettings();


	// terrain:
	static int getMapMaxX();
	static int getMapMaxY();
	static short getGenerationMetodth();
	static int getWorldSeed();

	static void setMapMaxX(int v_mapMaxX);
	static void setMapMaxY(int v_mapMaxY);
	static void setGenerationMetod(short v_generatinMetodth);
	static void setWorldSeed(int V_worldSeed);

	// buildings
	static float getBuildingsMaxDurabilityModidier();
	static float getBuildingExpansesMidifier();
	static float getBuildingsConstructionSpeedModifier();

	static void setBuildingsMaxDurabilityModidier(float value);
	static void setBuildingExpansesMidifier(float value);
	static void setBuildingsConstructionSpeedModifier(float value);

	~PreSettings();
};


#endif // !PRE_SETTINGS
