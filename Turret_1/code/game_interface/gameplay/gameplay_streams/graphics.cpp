
#include "game_interface/gameplay/gameplay.h"

#include "game_interface/main_window/main_window.h"
#include "game_interface/main_window/main_window_resize.h"

#include "game_interface/gameplay/gameplay_util/camera.h"
#include "t1_system/t1_mutex.h"

#include "game_interface/gameplay/ui_elements/exit_confirmation.h"
#include "game_interface/gameplay/ui_elements/settings_window.h"

#include "map_structures/entities/turret/turret.h"


void Gameplay::graphics(sf::RenderWindow& mainWindow)
{
    Camera t1camera;

    Building::prepareSprites();
    Turret::prepareSprites();
    ResourceUnit::prepareSprites();
    Entity::prepareSprites();
    Shell::prepareSprites();
    Particle::prepareSprites();

    sf::Event event;
    while (isGameplayActive)
    {
        t1camera.resize(mainWindow);

        mouseCoord = sf::Mouse::getPosition(mainWindow);
        mouseMapCoord = mainWindow.mapPixelToCoords(mouseCoord);

        while (mainWindow.pollEvent(event))
        {
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
                t1camera.updateMapRegion(mainWindow);
            }

            if (event.type == sf::Event::MouseWheelMoved)
            {
                t1camera.scale(event);
                mainWindow.setView(t1camera.camera);
                t1camera.updateMapRegion(mainWindow);
            }
        }

        if (isMovingCamera)
        {
            sf::Vector2f newMousePosition = mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow));
            sf::Vector2f delta = lastMousePosition - newMousePosition;

            t1camera.camera.move(delta);
            mainWindow.setView(t1camera.camera);
            t1camera.updateMapRegion(mainWindow);
        }


        mainWindow.clear(sf::Color::Black);		//Begin draw_block

        t1::system::mt::buildings.lock();
        TerrainMap::drawMap(mainWindow);
        BuildingsMap::drawMap(mainWindow);
        drawParticlesList(mainWindow);
        Team::drawAll(mainWindow);
        t1::system::mt::buildings.unlock();

        buildingPanel.drawBuildExample(mainWindow, mouseMapCoord, player.get());

        mainWindow.setView(overlay);						//	Draw_inteface block
        mainControlPanel.draw(mainWindow);
        mainControlPanel.interactWaveTimer(isPaused);
        buildingPanel.draw(mainWindow);
        resourcesPanel.draw(mainWindow);
        ConfirmationWindow::getInstance().draw(mainWindow);
        SettingsWindow::getInstance().draw(mainWindow);

        mainWindow.setView(t1camera.camera);

        mainWindow.display();		//End draw_block
    }
}
