
#include "game_interface/gameplay/gameplay.h"

#include "game_interface/main_window/main_window.h"
#include "game_interface/main_window/main_window_resize.h"

#include "t1_system/input/input_handler.h"

#include "game_interface/gameplay/gameplay_util/mob_controller.h"

#include "map_structures/buildings/building/building.h"
#include "map_structures/entities/turret/turret.h"

void Gameplay::graphics(sf::RenderWindow& mainWindow)
{
    TerrainMap::prepareSprites();
    Building::prepareSprites();
    BlueprintsMap::prepareSprites();
    Turret::prepareSprites();
    ResourceUnit::prepareSprites();
    Entity::prepareSprites();
    Shell::prepareSprites();
    Particle::prepareSprites();

    while (isGameplayActive)
    {
        while (const std::optional event = mainWindow.pollEvent())
        {
            InputHandler::updateInput(event);
            InputHandler::updateMouseCoord(mainWindow);

            if (event->is<sf::Event::Closed>())
            {
                mainWindow.close();
                isGameplayActive = false;
            }

            if (event->is<sf::Event::Resized>() || UIWindow::windowCreated)
            {
                UIWindow::windowCreated = false;
                overlayResize(mainWindow);
                relocateSubWindows(sf::Vector2i(mainWindow.getSize()));
            }
        }
        
        mainWindow.clear(sf::Color::Black);		//Begin draw_block
        camera.interact(mainWindow, MobController::getTarget(), isPaused);
        world.draw(mainWindow, camera);
        buildingPanel.drawBuildExample(mainWindow, player, world.getBuildingsMap());

        mainWindow.setView(overlay);			//Draw_inteface block
        mainControlPanel.draw(mainWindow);
        mainControlPanel.interactWaveTimer(isPaused, world);
        buildingPanel.draw(mainWindow);
        resourcesPanel.draw(mainWindow);
        inventoryWindow.draw(mainWindow);

        mainWindow.setView(camera.getView());
        mainWindow.display();                   //End draw_block
    }
}
