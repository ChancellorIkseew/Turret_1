#pragma once
#ifndef T1_BC_BUILDINGS_PAGES
#define T1_BC_BUILDINGS_PAGES

#include <map>
#include "game_interface/ui_window/elements/button/building_ico.h"

namespace t1::bc
{
	void initLogistics(std::map<uint16_t, BuildingIco>& logistics);
	void initDrills(std::map<uint16_t, BuildingIco>& factories);
	void initFactories(std::map<uint16_t, BuildingIco>& factories);
	void initElectrics(std::map<uint16_t, BuildingIco>& electrics);

	void initWalls(std::map<uint16_t, BuildingIco>& walls);
	void initTurrets(std::map<uint16_t, BuildingIco>& turrets);
	void initStorages(std::map<uint16_t, BuildingIco>& storages);
	void initSpecial(std::map<uint16_t, BuildingIco>& electrics);

	void initUtil(std::map<uint16_t, BuildingIco>& util);

	void arrangePage(std::map<uint16_t, BuildingIco>& page); // make order_of_ico-buttons 

}

#endif // T1_BC_BUILDINGS_PAGES
