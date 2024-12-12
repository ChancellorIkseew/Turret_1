
#include <iostream>
#include "game_interface/gameplay/gameplay.h"

#include "t1_system/input/input_handler.h"
#include "t1_system/sleep.h"

#include "game_interface/gameplay/gameplay_util/cheet_commands.h"
#include "game_interface/gameplay/ui_elements/main_control_panel.h"
#include "game_interface/gameplay/ui_elements/building_panel.h"


void Gameplay::input(sf::RenderWindow& mainWindow)
{
    while (isGameplayActive)
    {
        mainControlPanel.interact(isPaused, isGameplayActive);
        buildingPanel.interact(mouseMapCoord, player.get());
        inventoryWindow.interact(mouseMapCoord, player.get());

        if (InputHandler::active(t1::KeyName::MidMB))
        {
            if (!isMovingCamera)
            {
                isMovingCamera = true;
                lastMousePosition = mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow));
            }
        }
        else
        {
            isMovingCamera = false;
        }

#ifndef TURRET_1_NO_TEST_BUILD
        if (InputHandler::jactive(t1::KeyName::Console_cheat))
        {
            std::cout << "cheet_comands_panel_called" << '\n';
            acceptCheetCommand();
        }
#endif // TURRET_1_NO_TEST_BUILD

        t1::system::sleep(16);
    }
}
