
#include "game_interface/gameplay/gameplay.h"

#include "t1_system/sleep.h"
#include "t1_system/t1_mutex.h"
#include "game_interface/gameplay/gameplay_util/t1_time.h"
#include "game_interface/gameplay/gameplay_util/wave_constructor.h"

#include "map_structures/terrain/terrain.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/team/team.h"
#include "map_structures/particles/particles.h"

#include "game_interface/gameplay/ui_elements/resources_panel.h"
#include "t1_system/events/event_handler.h"


void Gameplay::simulation()
{
    while (isGameplayActive)
    {
        if (!isPaused)
        {
            BuildingsMap::pushChanges();


            //t1::res::useEnergy(time);
            t1::system::mt::buildings.lock();
            BuildingsMap::intetractMap();
            createWave(*enemy);
            Team::interactAll();
            moveParticlesList();
            t1::system::mt::buildings.unlock();
            t1::time::time++;
            EventsHandler::pollSimulationEvents();
        }
        resourcesPanel.interact(*player);

        t1::system::sleep(16);
    }
}
