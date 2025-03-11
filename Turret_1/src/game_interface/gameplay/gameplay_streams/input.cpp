
#include <iostream>
#include "game_interface/gameplay/gameplay.h"

#include "t1_system/input/input_handler.h"
#include "t1_system/sleep.h"

#include "game_interface/gameplay/gameplay_util/cheet_commands.h"
#include "game_interface/gameplay/ui_elements/main_control_panel.h"
#include "game_interface/gameplay/ui_elements/building_panel.h"
#include "game_interface/gameplay/gameplay_util/mob_controller.h"


void Gameplay::input()
{
    while (isGameplayActive)
    {
        mainControlPanel.interact(isPaused, isGameplayActive, tickSpeed, world);
        buildingPanel.interact(player, world.getBuildingsMap(), world.getBlueprintsMap(), *this);
        inventoryWindow.interact(player, world.getBuildingsMap());
        MobController::interact(*player, *this);

#ifndef NDEBUG
        if (InputHandler::jactive(t1::BindName::Console_cheat))
        {
            std::cout << "cheet_comands_panel_called\n";
            acceptCheetCommand();
        }
#endif // NDEBUG
        
        t1::system::sleep(16);
    }
    MobController::setTarget(nullptr);
}
