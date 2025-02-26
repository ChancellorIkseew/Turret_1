#pragma once
#ifndef T1_BC_BUILDINGS_PAGES
#define T1_BC_BUILDINGS_PAGES

#include <map>
#include "game_interface/ui_window/elements/button/building_ico.h"

enum class BuildingType : uint16_t;

namespace t1::bc
{
	void initLogistics(std::map<BuildingType, BuildingIco>& logistics);
	void initDrills(std::map<BuildingType, BuildingIco>& drills);
	void initFactories(std::map<BuildingType, BuildingIco>& factories);
	void initElectrics(std::map<BuildingType, BuildingIco>& electrics);

	void initWalls(std::map<BuildingType, BuildingIco>& walls);
	void initTurrets(std::map<BuildingType, BuildingIco>& turrets);
	void initStorages(std::map<BuildingType, BuildingIco>& storages);
	void initSpecial(std::map<BuildingType, BuildingIco>& electrics);

	void initUtil(std::map<BuildingType, BuildingIco>& util);

	void arrangePage(std::map<BuildingType, BuildingIco>& page); // make order_of_ico-buttons 

}

#endif // T1_BC_BUILDINGS_PAGES
