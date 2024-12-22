
#include "game_interface/gameplay/gameplay.h"

#include "t1_system/sleep.h"
#include "game_interface/gameplay/gameplay_util/t1_time.h"
#include "game_interface/gameplay/gameplay_util/wave_constructor.h"

#include "map_structures/terrain/terrain.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/team/team.h"
#include "map_structures/particles/particles.h"

#include "game_interface/gameplay/ui_elements/resources_panel.h"
#include "t1_system/events/events_handler.h"


void Gameplay::simulation()
{
    while (isGameplayActive)
    {
        if (!isPaused)
        {
            world.simulate();
            //createWave(*enemy, world.getBuildingsMap());
            t1::time::time++;
            EventsHandler::pollSimulationEvents();
        }
        resourcesPanel.interact(*player);

        t1::system::sleep(16);
    }
}
