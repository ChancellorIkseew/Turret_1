
#include <iostream>
#include "game_interface/gameplay/gameplay.h"

#include "t1_system/system.h"
#include "t1_system/sleep.h"

#include "game_interface/gameplay/gameplay_util/cheet_commands.h"
#include "game_interface/gameplay/ui_elements/main_control_panel.h"
#include "game_interface/gameplay/ui_elements/building_panel.h"


void Gameplay::input(sf::RenderWindow& mainWindow)
{
    while (isGameplayActive)
    {
        mainControlPanel.interact(mouseCoord, isPaused, isGameplayActive);
        buildingPanel.interact(mouseCoord, mouseMapCoord, player.get());

        if (MidMB_Pressed)
        {
            if (!isMovingCamera)
            {
                isMovingCamera = true;
                lastMousePosition = mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow));
            }
        }

        if (MidMB_Free)
        {
            isMovingCamera = false;
        }

#ifndef TURRET_1_NO_TEST_BUILD
        if (LEFT_ALT_Pressed)
        {
            std::cout << "cheet_comands_panel_called" << '\n';
            acceptCheetCommand();
        }
#endif // TURRET_1_NO_TEST_BUILD

        t1::system::sleep(16);
    }
}
