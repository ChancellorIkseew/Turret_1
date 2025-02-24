
#include "game_interface/gameplay/gameplay.h"
#include "t1_system/sleep.h"

void Gameplay::scripts()
{
   
    while (isGameplayActive)
    {
        if (!isPaused)
        {
            
        }
        t1::system::sleep(2000);
    }
}
