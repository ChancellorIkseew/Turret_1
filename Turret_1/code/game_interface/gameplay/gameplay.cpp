
#include <iostream>	
#include <SFML/Graphics.hpp>
#include <thread>
#include <list>

#include "gameplay.h"

#include "../main_window/main_window.h"
#include "../main_window/main_window_resize.h"
#include "../settings/settings_util/settings_save_system.h"


#include "gameplay_util/camera.h"
#include "gameplay_util/wave_constructor.h"
#include "gameplay_util/cheet_commands.h"

#include "../system/system.h"
#include "../../map_structures/base_engine/t1_mutex.h"


#include "sub_windows/sub_windows_util/sub_windows_list.h"
#include "sub_windows/specifications_panel.h"


#include "../../map_structures/pre-settings/pre-settings.h"

#include "../../map_structures/buildings/building/buildings_info.h"

#include "../../map_structures/entities/turrets.h"
#include "../../map_structures/entities/entities.h"
#include "../../map_structures/entities/entities_util/entities_list.h"

#include "../../map_structures/shells/shells.h"
#include "../../map_structures/shells/shell_types/rockets.h"

#include "../../map_structures/particles/particles.h"

#include "../../map_structures/resources/resource_units.h"


char startGameplay(sf::RenderWindow& mainWindow, bool startNewGame, std::string saveFolderName)
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

	//startNewGame
	if (startNewGame)
	{
		std::cout << "create new works" << std::endl;

		map1.mapGeneration();
		buildingsMap1.generateMap();

		giveStartResources();
	}
	else
	{
		std::cout << "save open works" << std::endl;
		map1.loadMap();
		buildingsMap1.loadMap();
		loadEntitiesList(saveFolderName);
        loadResUnitsList(saveFolderName);

		time = loadTime(saveFolderName);
		loadResources(saveFolderName);
	}
	

    
    bool isPaused = true;
    bool isBuildingTypeSelected = false;		//from select_building_button
    int buildingType = 0;					//from select_building_button

	bool isGameplayActive = true;

    std::thread simulation([&]()
        {
            while (isGameplayActive)
            {
                if (!isPaused)			//Begin action_block
                {
                    useEnergy(time);

                    mtBuildings.lock();
                    buildingsMap1.intetractMap();
                    createWave(time);
                    moveEntitiesList(buildingsMap1, time);
                    buildingsMap1.cleanMapChanged();
                    moveShellsList(time);
                    checkShellsHitting(buildingsMap1);
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
                    mainControlPanel.interact(mouseCoord, time, isPaused, isGameplayActive, saveFolderName);
                    buildingPanel.interact(mouseCoord, mouseMapCoord, isBuildingTypeSelected, buildingType);

                    Sleep(150);
                }

                if (RMB_Pressed)
                {
                    buildingPanel.rotateBuilding(buildingType);
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

                #ifndef TURRET_NO_TEST_BUILD
                if (LEFT_ALT_Pressed)
                {
                    std::cout << "cheet_comands_panel_called" << '\n';
                    acceptCheetCommand();
                }
                #endif // TURRET_NO_TEST_BUILD

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
        drawParticlesList(mainWindow, time);
		drawEntitiesList(mainWindow);
		drawShellsList(mainWindow, time);
        mtBuildings.unlock();
	    
        if(isBuildingTypeSelected)
		{   
			buildingPanel.drawBuildExample(mainWindow ,mouseMapCoord, buildingType);
           	SpecificationsPanel::getInstance()->interact(mainWindow, buildingType);
		}
        
        
        mainWindow.setView(overlay);						//	Draw_inteface block
        
        mainControlPanel.draw(mainWindow);
        mainControlPanel.interactWaveTimer(time, isPaused);
        
		buildingPanel.draw(mainWindow);
		
		resWin.interactResourcesPanel(mainWindow); //Resourses_panel
		resWin.drawResourcesPanel(mainWindow); 	//Resourses_panel
		
		if(isBuildingTypeSelected)
		{
			SpecificationsPanel::getInstance()->draw(mainWindow);	//Specification_panel
		}

		
        confWin.draw(mainWindow);
        settingsWindow.draw(mainWindow);

		mainWindow.setView(t1camera.camera);
		
		mainWindow.display();		//End draw_block
	}

    simulation.join();
    input.join();

	return GameCondition::MAIN_MENU;
}