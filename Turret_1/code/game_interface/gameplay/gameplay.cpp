
#include <iostream>	
#include <thread>

#include "gameplay.h"

#include "game_interface/main_window/main_window.h"

#include "game_interface/gameplay/gameplay_streams/simulation.h"
#include "game_interface/gameplay/gameplay_streams/input.h"
#include "game_interface/gameplay/gameplay_streams/graphics.h"

#include "gameplay_util/t1_time.h"

#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/terrain/terrain.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/resources/resource_units.h"
#include "map_structures/resources/resources.h"
#include "map_structures/particles/particles.h"
#include "map_structures/team/team.h"
#include "map_structures/buildings/building/buildings_enum.h"


char t1::gamepl::startGameplay(sf::RenderWindow& mainWindow, bool startNewGame, std::string saveFolderName)
{
    if (!startNewGame)
    {
        PreSettings::loadPreSettings();
    }

	TerrainMap terrainMap(PreSettings::getMapSize());
	BuildingsMap buildingsMap(PreSettings::getMapSize());
    Entity::initPreSettings();

    std::shared_ptr<Team> player = std::make_shared<Team>("player");
    std::shared_ptr<Team> enemy = std::make_shared<Team>("enemy");

    Team::addTeam(player);
    Team::addTeam(enemy);

	if (startNewGame)
	{
		std::cout << "create new works" << std::endl;

        TerrainMap::generateMap();
        BuildingsMap::constructBuilding(CORE_MK1, 0, { 48, 48 }, player.get());

        t1::time::resetTime();
        //t1::res::giveStartResources();
	}
	else
	{
		std::cout << "save open works" << std::endl;
        TerrainMap::loadMap(saveFolderName);
		BuildingsMap::loadMap(saveFolderName);
		//loadEntitiesList(saveFolderName);
        loadResUnitsList(saveFolderName);

        t1::time::loadTime(saveFolderName);
        //t1::res::loadResources(saveFolderName);
	}
	
    bool isMovingCamera = false;
    sf::Vector2f lastMousePosition;

    sf::Vector2i mouseCoord;
    sf::Vector2f mouseMapCoord;
    
    bool isPaused = true;
	bool isGameplayActive = true;

    std::thread simulation([&]() { t1::gamepl::simulation(isGameplayActive, isPaused, *enemy, *player); });
    std::thread input([&]() { t1::gamepl::input(isGameplayActive, isPaused, mainWindow, mouseCoord, mouseMapCoord,
        lastMousePosition, isMovingCamera, saveFolderName, player.get()); });
    graphics(isGameplayActive, isPaused, mainWindow, mouseCoord, mouseMapCoord,
        lastMousePosition, isMovingCamera);
    if (false)
    {
        //std::thread network([&]() { network(); } );
    }

    simulation.join();
    input.join();

	return GameCondition::MAIN_MENU;
}
