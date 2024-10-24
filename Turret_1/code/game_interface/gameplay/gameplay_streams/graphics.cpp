
#include "graphics.h"

#include "game_interface/main_window/main_window.h"
#include "game_interface/main_window/main_window_resize.h"

#include "game_interface/gameplay/gameplay_util/camera.h"
#include "t1_system/t1_mutex.h"

#include "game_interface/gameplay/ui_elements/exit_confirmation.h"
#include "game_interface/gameplay/ui_elements/settings_window.h"
#include "game_interface/gameplay/ui_elements/resources_panel.h"
#include "game_interface/gameplay/ui_elements/main_control_panel.h"
#include "game_interface/gameplay/ui_elements/specifications_panel.h"
#include "game_interface/gameplay/ui_elements/building_panel.h"

#include "map_structures/terrain/terrain.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/entities/turret/turret.h"
#include "map_structures/entities/entity/entity.h"
#include "map_structures/shells/shell/shell.h"
#include "map_structures/resources/resource_unit.h"
#include "map_structures/particles/particles.h"
#include "map_structures/team/team.h"


void t1::gamepl::graphics(bool& isGameplayActive, const bool& isPaused, sf::RenderWindow& mainWindow,
    sf::Vector2i& mouseCoord, sf::Vector2f& mouseMapCoord, sf::Vector2f& lastMousePosition,
    bool& isMovingCamera)
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

            if (event.type == sf::Event::Resized)
            {
                overlayResize(mainWindow);
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
        //drawResUnitsList(mainWindow);
        drawParticlesList(mainWindow);
        Team::drawAll(mainWindow);
        t1::system::mt::buildings.unlock();

        BuildingPanel::getInstance().drawBuildExample(mainWindow, mouseMapCoord);

        mainWindow.setView(overlay);						//	Draw_inteface block
        MainControlPanel::getInstance().draw(mainWindow);
        MainControlPanel::getInstance().interactWaveTimer(isPaused);
        BuildingPanel::getInstance().draw(mainWindow);
        ResourcesPanel::getInstance().draw(mainWindow);
        ConfirmationWindow::getInstance().draw(mainWindow);
        SettingsWindow::getInstance().draw(mainWindow);

        mainWindow.setView(t1camera.camera);

        mainWindow.display();		//End draw_block
    }
}
