#ifndef NDEBUG

#include "save_load.h"
#include "map_structures/world/world.h"

void saveLoadTest(World& world)
{
	BuildingsMap& buildingsMap = world.getBuildingsMap();



	world.save("test_save");


	world.load("test_save");

}

#endif // NDEBUG
