
#include <iostream>	
#include <SFML/Graphics.hpp>
#include <thread>

#include "gameplay.h"

#include "game_interface/main_window/main_window.h"
#include "game_interface/main_window/main_window_resize.h"

#include "game_interface/gameplay/gameplay_streams/simulation.h"
#include "game_interface/gameplay/gameplay_streams/input.h"

#include "gameplay_util/camera.h"
#include "gameplay_util/t1_time.h"
#include "map_structures/base_engine/t1_mutex.h"

#include "sub_windows/exit_confirmation.h"
#include "sub_windows/settings_window.h"
#include "sub_windows/resources_panel.h"
#include "sub_windows/main_control_panel.h"
#include "sub_windows/specifications_panel.h"
#include "sub_windows/building_panel.h"

#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/terrain/terrain.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/entities/turret/turret.h"
#include "map_structures/entities/entities_list/entities_list.h"
#include "map_structures/shells/shells_list/shells_list.h"
#include "map_structures/resources/resource_units.h"
#include "map_structures/resources/resources.h"
#include "map_structures/particles/particles.h"


char t1::gamepl::startGameplay(sf::RenderWindow& mainWindow, bool startNewGame, std::string saveFolderName)
{
    oldWinSizeX = 0;
	
    
    if (!startNewGame)
    {
        PreSettings::loadPreSettings();
    }

	TerrainMap terrainMap(PreSettings::getMapSize());
	BuildingsMap buildingsMap(PreSettings::getMapSize());
    Entity::initPreSettings();

    Building::prepareSprites();
    Turret::prepareSprites();
    ResourceUnit::prepareSprites();
	Entity::prepareSprites();
	Shell::prepareSprites();
	Particle::prepareSprites();

	if (startNewGame)
	{
		std::cout << "create new works" << std::endl;

        TerrainMap::generateMap();
        BuildingsMap::generateMap();

        t1::time::resetTime();
        t1::res::giveStartResources();
	}
	else
	{
		std::cout << "save open works" << std::endl;
        TerrainMap::loadMap(saveFolderName);
		BuildingsMap::loadMap(saveFolderName);
		loadEntitiesList(saveFolderName);
        loadResUnitsList(saveFolderName);

        t1::time::loadTime(saveFolderName);
        t1::res::loadResources(saveFolderName);
	}
	
    Camera t1camera;
    bool isMovingCamera = false;
    sf::Vector2f lastMousePosition;

    sf::Vector2i mouseCoord;
    sf::Vector2f mouseMapCoord;
    
    bool isPaused = true;
	bool isGameplayActive = true;

    std::thread simulation([&]() { t1::gamepl::simulation(isGameplayActive, isPaused); });
    std::thread input([&]() { t1::gamepl::input(isGameplayActive, isPaused, mainWindow, mouseCoord, mouseMapCoord,
        lastMousePosition, isMovingCamera, saveFolderName); });


    while (isGameplayActive)
    {
        overlayResize(mainWindow);
        t1camera.resize(mainWindow);
        //t1camera.updateMapRegion(mainWindow);
    	
    	mouseCoord = sf::Mouse::getPosition(mainWindow);
		mouseMapCoord = mainWindow.mapPixelToCoords(mouseCoord);
    	
        sf::Event event;
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
        
        mtBuildings.lock();
        TerrainMap::drawMap(mainWindow);
        BuildingsMap::drawMap(mainWindow);
        drawResUnitsList(mainWindow);
        drawParticlesList(mainWindow);
		drawEntitiesList(mainWindow);
        t1::sh::drawShellsList(mainWindow);
        mtBuildings.unlock();

        BuildingPanel::getInstance().drawBuildExample(mainWindow ,mouseMapCoord);

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

    simulation.join();
    input.join();

	return GameCondition::MAIN_MENU;
}
