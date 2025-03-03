
#include "game_interface/gameplay/gameplay.h"

#include "t1_system/sleep.h"
#include "game_interface/gameplay/gameplay_util/wave_constructor.h"
#include "game_interface/gameplay/ui_elements/resources_panel.h"
//#include "map_structures/entities/entity/mob_enum.h"


void Gameplay::simulation()
{
    Team& enemy = *world.getTeam("enemy");
    //WaveConstructor::spawnTestWave(enemy, world.getBuildingsMap()); //test
    WaveConstructor::spawnTestWave(*player, world.getBuildingsMap()); //test
    //player->spawnEntity(1, MobType::ROCKET_BOSS, world.getBuildingsMap());
    //MobController::setTarget(player->getEneities().getList().begin()->get());
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
