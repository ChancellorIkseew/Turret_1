
#include <iostream>	
#include <thread>

#include "gameplay.h"

#include "game_interface/main_window/main_window.h"

#include "gameplay_util/t1_time.h"

#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/terrain/terrain.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/particles/particles.h"
#include "map_structures/team/team.h"
#include "map_structures/buildings/building/buildings_enum.h"

#include "game_interface/gameplay/ui_elements/exit_confirmation.h"
#include "game_interface/gameplay/ui_elements/settings_window.h"

#include "map_structures/world/world.h"

int Gameplay::startGameplay(sf::RenderWindow& mainWindow, bool startNewGame, std::string saveFolderName)
{
	if (!startNewGame)
	{
		PreSettings::load();
	}

	World world;
	//TerrainMap terrainMap(PreSettings::getTerrain().mapSize);
	//BuildingsMap buildingsMap(PreSettings::getTerrain().mapSize);
	//Entity::initPreSettings();
	//player = std::make_shared<Team>("player");
	//enemy = std::make_shared<Team>("enemy");
	//Team::addTeam(player);
	//Team::addTeam(enemy);

	if (startNewGame)
	{
		std::cout << "create new works" << std::endl;

		//TerrainMap::generateMap();
		//BuildingsMap::placeBuilding(CORE_MK2, 0, { 48, 48 }, player.get());

		t1::time::resetTime();
		player->balance.giveStartRes(PreSettings::getGeneral().startBalance);
	}
	else
    {
		std::cout << "load world works" << std::endl;
		world.load("saves/try.bin");
    }

    //std::thread simulation([&]() { simulation(); });
    std::thread input([&]() { input(mainWindow); });
    //std::thread network([&]() { network(); } ); not implemented
    graphics(mainWindow);

    //simulation.join();
    input.join();
	//network.join(); not implemented
    //Team::teams.clear();
	return GameCondition::MAIN_MENU;
}



void Gameplay::relocateSubWindows(const sf::Vector2u windowSize)
{
	ConfirmationWindow::getInstance().relocate(windowSize);
	SettingsWindow::getInstance().relocate(windowSize);
	resourcesPanel.relocate(windowSize);
	buildingPanel.relocate(windowSize);
}



bool Gameplay::noSubWindowSelected()
{
	return (!mainControlPanel.containsCoursor() && !resourcesPanel.containsCoursor() &&
		!buildingPanel.containsCoursor());
}


Gameplay::Gameplay()
{
	instance = this;
}

Gameplay::~Gameplay()
{
	instance = nullptr;
}

Gameplay* Gameplay::getInstance()
{
	return instance;
}
