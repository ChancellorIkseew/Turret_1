
#include "simulation.h"

#include "game_interface/system/sleep.h"
#include "map_structures/base_engine/t1_mutex.h"
#include "game_interface/gameplay/gameplay_util/t1_time.h"
#include "game_interface/gameplay/gameplay_util/wave_constructor.h"

#include "map_structures/terrain/terrain.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/entities/turret/turret.h"
#include "map_structures/entities/entities_list/entities_list.h"
#include "map_structures/shells/shells_list/shells_list.h"
#include "map_structures/resources/resource_units.h"
#include "map_structures/particles/particles.h"


void t1::gamepl::simulation(const bool& isGameplayActive, const bool& isPaused)
{
    while (isGameplayActive)
    {
        if (!isPaused)
        {
            //t1::res::useEnergy(time);
            mtBuildings.lock();
            BuildingsMap::intetractMap();
            createWave();
            moveEntitiesList();
            BuildingsMap::cleanMapChanged();
            t1::sh::moveShellsList();
            moveParticlesList();
            moveResUnitsList(t1::time::time);
            mtBuildings.unlock();
            t1::time::time++;
        }
        t1::system::sleep(16);
    }
}
