
#include "game_interface/gameplay/gameplay.h"

#include "t1_system/sleep.h"
#include "game_interface/gameplay/gameplay_util/t1_time.h"
#include "game_interface/gameplay/gameplay_util/wave_constructor.h"

#include "game_interface/gameplay/ui_elements/resources_panel.h"



void Gameplay::simulation()
{
    while (isGameplayActive)
    {
        if (!isPaused)
        {
            world.simulate();
            WaveConstructor::createWave(*enemy, world);
        }
        resourcesPanel.interact(*player);
        t1::system::sleep(16);
    }
}
