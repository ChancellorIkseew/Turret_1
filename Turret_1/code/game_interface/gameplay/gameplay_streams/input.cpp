
#include <iostream>

#include "input.h"

#include "game_interface/system/system.h"
#include "game_interface/system/sleep.h"

#include "game_interface/gameplay/gameplay_util/cheet_commands.h"
#include "game_interface/gameplay/sub_windows/main_control_panel.h"
#include "game_interface/gameplay/sub_windows/building_panel.h"


void t1::gamepl::input(bool& isGameplayActive, bool& isPaused, sf::RenderWindow& mainWindow,
    sf::Vector2i& mouseCoord, sf::Vector2f& mouseMapCoord, sf::Vector2f& lastMousePosition,
    bool& isMovingCamera, const std::string& saveFolderName, Team* team)
{
    while (isGameplayActive)
    {
        MainControlPanel::getInstance().interact(mouseCoord, isPaused, isGameplayActive, saveFolderName);


        if (LMB_Pressed)
        {
            
            BuildingPanel::getInstance().interact(mouseCoord, mouseMapCoord, team);

            Sleep(150);
        }

        if (RMB_Pressed)
        {
            BuildingPanel::getInstance().rotateBuilding();
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
