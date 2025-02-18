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
	GeneralPre general;
	TerrainPre terrain;
	BuildingsPre buildings;
	MobsPre mobs;
	ShellsPre shells;
	TimerPre timer;

public:
	PreSettings() = default;
	~PreSettings() = default;

	void load(const std::string& saveFolderName);
	void save(const std::string& saveFolderName) const;
	
	const GeneralPre& getGeneral() const { return general; }
	const TerrainPre& getTerrain() const { return terrain; }
	const BuildingsPre& getBuildings() const { return buildings; }
	const MobsPre& getMobs() const { return mobs; }
	const ShellsPre& getShells() const { return shells; }
	const TimerPre& getTimer() const { return timer; }

	GeneralPre& changeGeneral() { return general; }
	TerrainPre& changeTerrain() { return terrain; }
	BuildingsPre& changeBuildings() { return buildings; }
	MobsPre& changeMobs() { return mobs; }
	ShellsPre& changeShells() { return shells; }
	TimerPre& changeTimer() { return timer; }

};


#endif // MAP_STR_PRE_SETTINGS
