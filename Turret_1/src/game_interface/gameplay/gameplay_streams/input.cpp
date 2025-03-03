
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
        sf::Vector2f mouseMapCoord = InputHandler::getMouseMapCoord();
        mainControlPanel.interact(isPaused, isGameplayActive, world);
        buildingPanel.interact(mouseMapCoord, player, world.getBuildingsMap(), *this);
        inventoryWindow.interact(player, world.getBuildingsMap());
        MobController::interact(*player);

#ifndef TURRET_1_NO_TEST_BUILD
        if (InputHandler::jactive(t1::BindName::Console_cheat))
        {
            std::cout << "cheet_comands_panel_called\n";
            acceptCheetCommand();
        }
#endif // TURRET_1_NO_TEST_BUILD
        
        t1::system::sleep(16);
    }
    MobController::setTarget(nullptr);
}
