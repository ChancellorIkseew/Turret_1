
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


GameState Gameplay::startGameplay(sf::RenderWindow& mainWindow, bool startNewGame, std::string saveFolderName, std::optional<PreSettings> preSettings)
{
	player = std::make_shared<Team>("player");
	enemy = std::make_shared<Team>("enemy");
	world.addTeam(player);
	world.addTeam(enemy);

	if (startNewGame)
	{
		std::cout << "create new works" << std::endl;
		world.createNew(preSettings.value());
		world.getBuildingsMap().placeBuilding(BuildingType::CORE_MK2, 0, {48, 48}, player.get());
		t1::Time::resetTime();
		player->balance.giveStartRes(preSettings.value().getGeneral().startBalance);
	}
	else
    {
		std::cout << "load world works" << std::endl;
		//PreSettings::load("save_1");
		world.load("save_1");
    }

	camera = Camera(world.getPreSettings().getTerrain().mapSize);

	std::thread simulation(&Gameplay::simulation, this);
	std::thread input(&Gameplay::input, this);
	//std::thread network(&Gameplay::network, this);  not implemented
    graphics(mainWindow);

    simulation.join();
    input.join();
	//network.join(); not implemented
	return GameState::MAIN_MENU;
}


void Gameplay::relocateSubWindows(const sf::Vector2u windowSize)
{
	ConfirmationWindow::getInstance().relocate(windowSize);
	SettingsWindow::getInstance().relocate(windowSize);
	resourcesPanel.relocate(windowSize);
	buildingPanel.relocate(windowSize);
}

bool Gameplay::noSubWindowSelected() const
{
	return (!mainControlPanel.containsCoursor() && !resourcesPanel.containsCoursor() &&
		!buildingPanel.containsCoursor());
}
