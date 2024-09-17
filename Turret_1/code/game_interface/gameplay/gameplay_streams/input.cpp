
#include <iostream>
//#include <Windows.h>

#include "input.h"

//#include "../../system/system.h" //

#include "../sub_windows/sub_windows_util/sub_windows_list.h" //
#include "../gameplay_util/select_building_button.h"
#include "../gameplay_util/cheet_commands.h"


void input(bool& isGameplayActive)
{
    
    while (isGameplayActive)
    {
        if (LMB_Pressed)
        {
            mainControlPanel.interact(mouseCoord, map1, buildingsMap1, time, isPaused, isGameplayActive, saveFolderName);
            buildingPanel.interact(mouseCoord, mouseMapCoord, map1, buildingsMap1, index);

            Sleep(150);
        }

        if (RMB_Pressed)
        {
            rotateBuilding();
            Sleep(150);
        }

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

        if (LEFT_ALT_Pressed)
        {
            std::cout << "cheet_comands_panel_called" << '\n';
            acceptCheetCommand();
        }

        Sleep(16);
    }
    
}
