
#include "game_interface/gameplay/gameplay.h"

#include "t1_system/sleep.h"
#include "t1_system/events/events_handler.h"
#include "game_interface/gameplay/gameplay_util/wave_constructor.h"
#include "game_interface/gameplay/ui_elements/resources_panel.h"

constexpr int TICK = 16;

void Gameplay::simulation()
{
    BlueprintsMap::initTeam(player);
    Team& enemy = *world.getTeam("enemy");
    //WaveConstructor::spawnTestWave(enemy, world.getPreSettings().getTerrain().mapSize); //test
    minimap.interact(world);
    while (isGameplayActive)
    {
        if (!isPaused)
        {
            world.simulate();
            WaveConstructor::createWave(enemy, world);
            if (world.getTime().getTime() % 30 == 0) // temporary ipmlementation
                minimap.interact(world);
        }
        resourcesPanel.interact(*player);
        t1::system::sleep(TICK / tickSpeed.load(std::memory_order_relaxed));
    }
    EventsHandler::clearEvents();
}
