#pragma once
#ifndef MAP_STR_PRE_SETTINGS
#define MAP_STR_PRE_SETTINGS

#include <string>

#include "pre_settings/general_pre.h"
#include "pre_settings/terrain_pre.h"
#include "pre_settings/buildings_pre.h"
#include "pre_settings/mobs_pre.h"
#include "pre_settings/shells_pre.h"
#include "pre_settings/timer_pre.h"


class PreSettings
{
private:
	static inline std::string saveFileName = "0";

	static inline GeneralPre general;
	static inline TerrainPre terrain;
	static inline BuildingsPre buildings;
	static inline MobsPre mobs;
	static inline ShellsPre shells;
	static inline TimerPre timer;

public:
	PreSettings(std::string saveFolderName);
	~PreSettings() = default;

	static void load();
	static void save();
	
	static const GeneralPre& getGeneral() { return general; }
	static const TerrainPre& getTerrain() { return terrain; }
	static const BuildingsPre& getBuildings() { return buildings; }
	static const MobsPre& getMobs() { return mobs; }
	static const ShellsPre& getShells() { return shells; }
	static const TimerPre& getTimer() { return timer; }

	static GeneralPre& changeGeneral() { return general; }
	static TerrainPre& changeTerrain() { return terrain; }
	static BuildingsPre& changeBuildings() { return buildings; }
	static MobsPre& changeMobs() { return mobs; }
	static ShellsPre& changeShells() { return shells; }
	static TimerPre& changeTimer() { return timer; }

};


#endif // MAP_STR_PRE_SETTINGS
