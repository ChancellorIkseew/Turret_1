
#include "game_interface/gameplay/gameplay.h"

#include "game_interface/main_window/main_window.h"

#include "t1_system/input/input_handler.h"

#include "game_interface/gameplay/gameplay_util/mob_controller.h"
#include "game_interface/sound_system/sound_system.h"
#include "t1_system/t1_mutex.h"


void Gameplay::graphics(sf::RenderWindow& mainWindow)
{
    while (isGameplayActive)
    {
        while (const std::optional event = mainWindow.pollEvent())
        {
            InputHandler::updateInput(event);
            InputHandler::updateMouseCoord(mainWindow);
            SoundSystem::updateSounds(camera);

            if (event->is<sf::Event::Closed>())
            {
                isGameplayActive = false;
                mainWindow.close(); 
            }

            if (event->is<sf::Event::Resized>() || UIWindow::windowCreated)
            {
                UIWindow::windowCreated = false;
                MainWindow::resize(mainWindow);
                relocateSubWindows(sf::Vector2i(mainWindow.getSize()));
            }
        }
        
        mainWindow.clear(sf::Color::Black);		//Begin draw_block
        camera.interact(mainWindow, MobController::getTarget(), isPaused);
        std::lock_guard guard(t1::system::mt::drawing);
        world.draw(mainWindow, camera);
        buildingPanel.drawBuildExample(mainWindow, player, world.getBuildingsMap());

        mainWindow.setView(MainWindow::getOverlay());			//Draw_inteface block
        mainControlPanel.draw(mainWindow);
        mainControlPanel.interactWaveTimer(isPaused, world);
        buildingPanel.draw(mainWindow);
        resourcesPanel.draw(mainWindow);
        inventoryWindow.draw(mainWindow);
        minimap.draw(mainWindow);

        mainWindow.setView(camera.getView());
        mainWindow.display();                   //End draw_block
    }

    SoundSystem::clearSounds();
}
