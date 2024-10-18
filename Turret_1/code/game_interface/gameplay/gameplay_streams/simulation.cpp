
#include "simulation.h"

#include "t1_system/sleep.h"
#include "t1_system/t1_mutex.h"
#include "game_interface/gameplay/gameplay_util/t1_time.h"
#include "game_interface/gameplay/gameplay_util/wave_constructor.h"

#include "map_structures/terrain/terrain.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/team/team.h"
#include "map_structures/resources/resource_units.h"
#include "map_structures/particles/particles.h"

#include "game_interface/gameplay/ui_elements/resources_panel.h"


void t1::gamepl::simulation(const bool& isGameplayActive, const bool& isPaused, Team& enemy, Team& player)
{
    while (isGameplayActive)
    {
        if (!isPaused)
        {
            //t1::res::useEnergy(time);
            t1::system::mt::buildings.lock();
            BuildingsMap::intetractMap();
            createWave(enemy);
            Team::interactAll();
            moveParticlesList();
            moveResUnitsList(t1::time::time);
            t1::system::mt::buildings.unlock();
            t1::time::time++;
        }
        ResourcesPanel::getInstance().interact(player);

        t1::system::sleep(16);
    }
}
