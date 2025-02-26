
#include "game_interface/gameplay/gameplay.h"

#include "game_interface/main_window/main_window.h"
#include "game_interface/main_window/main_window_resize.h"

#include "t1_system/input/input_handler.h"
#include "t1_system/t1_mutex.h"

#include "game_interface/gameplay/ui_elements/exit_confirmation.h"
#include "game_interface/gameplay/ui_elements/settings_window.h"

#include "map_structures/buildings/building/building.h"
#include "map_structures/entities/turret/turret.h"
#include <iostream>

void Gameplay::graphics(sf::RenderWindow& mainWindow)
{
    TerrainMap::prepareSprites();
    Building::prepareSprites();
    Turret::prepareSprites();
    ResourceUnit::prepareSprites();
    Entity::prepareSprites();
    Shell::prepareSprites();
    Particle::prepareSprites();

    sf::Event event;
    while (isGameplayActive)
    {
        while (mainWindow.pollEvent(event))
        {
            InputHandler::updateInput(event);
            InputHandler::updateMouseCoord(mainWindow);

            if (event.type == sf::Event::Closed)
            {
                mainWindow.close();
                isGameplayActive = false;
            }

            if (event.type == sf::Event::Resized || UIWindow::windowCreated)
            {
                UIWindow::windowCreated = false;
                overlayResize(mainWindow);
                relocateSubWindows(mainWindow.getSize());
            }
        }
        
        mainWindow.clear(sf::Color::Black);		//Begin draw_block
        camera.interact(mainWindow);
        world.draw(mainWindow, camera);
        buildingPanel.drawBuildExample(mainWindow, player, world.getBuildingsMap());

        mainWindow.setView(overlay);			//Draw_inteface block
        mainControlPanel.draw(mainWindow);
        mainControlPanel.interactWaveTimer(isPaused, world);
        buildingPanel.draw(mainWindow);
        resourcesPanel.draw(mainWindow);
        inventoryWindow.draw(mainWindow);
        ConfirmationWindow::getInstance().draw(mainWindow);
        SettingsWindow::getInstance().draw(mainWindow);

        mainWindow.setView(camera.getView());
        mainWindow.display();                   //End draw_block
    }
}
