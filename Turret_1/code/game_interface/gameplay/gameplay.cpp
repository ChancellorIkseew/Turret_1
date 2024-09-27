
#include <iostream>	
#include <SFML/Graphics.hpp>
#include <thread>

#include "gameplay.h"

#include "game_interface/main_window/main_window.h"
#include "game_interface/main_window/main_window_resize.h"
#include "game_interface/settings/settings_util/settings_save_system.h"


#include "gameplay_util/camera.h"
#include "gameplay_util/wave_constructor.h"
#include "gameplay_util/cheet_commands.h"

#include "game_interface/system/system.h"
#include "map_structures/base_engine/t1_mutex.h"


#include "sub_windows/sub_windows_util/sub_windows_list.h"
#include "sub_windows/exit_confirmation.h"
#include "sub_windows/settings_window.h"
#include "sub_windows/resources_panel.h"
#include "sub_windows/main_control_panel.h"
#include "sub_windows/specifications_panel.h"
#include "sub_windows/building_panel.h"


#include "map_structures/pre-settings/pre-settings.h"

#include "map_structures/buildings/building/buildings_info.h"

#include "map_structures/terrain/terrain.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/entities/turret/turret.h"
#include "map_structures/entities/entity/entity.h"
#include "map_structures/entities/entities_list/entities_list.h"
#include "map_structures/shells/shell/shell.h"
#include "map_structures/shells/shells_list/shells_list.h"

#include "map_structures/particles/particles.h"

#include "map_structures/resources/resource_units.h"


char t1::gamepl::startGameplay(sf::RenderWindow& mainWindow, bool startNewGame, std::string saveFolderName)
{
    oldWinSizeX = 0;

	int time = 0;

    Camera t1camera;

    bool isMovingCamera = false;
    sf::Vector2f lastMousePosition;
    
    sf::Vector2i mouseCoord;
    sf::Vector2f mouseMapCoord;
    
    if (!startNewGame)
    {
        PreSettings::loadPreSettings();
    }

	TerrainMap map1(saveFolderName);
	BuildingsMap buildingsMap1(saveFolderName);
    Entity::initPreSettings();

    Building::prepareSprites();
    Turret::prepareSprites();
    ResourceUnit::prepareSprites();
	Entity::prepareSprites();
	Shell::prepareSprites();
	Particle::prepareSprites();

    initBuildingsInfo();

	if (startNewGame)
	{
		std::cout << "create new works" << std::endl;

		map1.mapGeneration();
		buildingsMap1.generateMap();

        t1::res::giveStartResources();
	}
	else
	{
		std::cout << "save open works" << std::endl;
		map1.loadMap();
		buildingsMap1.loadMap();
		loadEntitiesList(saveFolderName);
        loadResUnitsList(saveFolderName);

		time = loadTime(saveFolderName);
        t1::res::loadResources(saveFolderName);
	}
	

    
    bool isPaused = true;
	bool isGameplayActive = true;

    std::thread simulation([&]()
        {
            while (isGameplayActive)
            {
                if (!isPaused)			//Begin action_block
                {
                    t1::res::useEnergy(time);

                    mtBuildings.lock();
                    buildingsMap1.intetractMap();
                    createWave(time);
                    moveEntitiesList();
                    buildingsMap1.cleanMapChanged();
                    t1::sh::moveShellsList(time);
                    t1::sh::checkShellsHitting();
                    moveParticlesList();
                    moveResUnitsList(time);
                    mtBuildings.unlock();

                    time++;
                }						//End action_block
                Sleep(16);
            }
        }
    );

    std::thread input([&]()
        {
            while (isGameplayActive)
            {
                if (LMB_Pressed)
                {
                    MainControlPanel::getInstance().interact(mouseCoord, time, isPaused, isGameplayActive, saveFolderName);
                    BuildingPanel::getInstance().interact(mouseCoord, mouseMapCoord);

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

                Sleep(16);
            }
        }

    );

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
        map1.drawMap(mainWindow);
        buildingsMap1.drawMap(mainWindow);
        drawResUnitsList(mainWindow);
        drawParticlesList(mainWindow);
		drawEntitiesList(mainWindow);
        t1::sh::drawShellsList(mainWindow, time);
        mtBuildings.unlock();

        BuildingPanel::getInstance().drawBuildExample(mainWindow ,mouseMapCoord);

        mainWindow.setView(overlay);						//	Draw_inteface block
        MainControlPanel::getInstance().draw(mainWindow);
        MainControlPanel::getInstance().interactWaveTimer(time, isPaused);
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
