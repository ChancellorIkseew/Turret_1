
#include "game_interface/gameplay/gameplay.h"

#include "t1_system/sleep.h"
#include "game_interface/gameplay/gameplay_util/wave_constructor.h"
#include "game_interface/gameplay/ui_elements/resources_panel.h"


void Gameplay::simulation()
{
    Team& enemy = *world.getTeam("enemy");
    WaveConstructor::spawnTestWave(enemy, world.getBuildingsMap()); //test
    WaveConstructor::spawnTestWave(*player, world.getBuildingsMap()); //test
    while (isGameplayActive)
    {
        if (!isPaused)
        {
            world.simulate();
            WaveConstructor::createWave(enemy, world);
        }
        resourcesPanel.interact(*player);
        t1::system::sleep(16);
    }
}
