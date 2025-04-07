
#include <thread>

#include "gameplay.h"

#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"
#include "game_interface/gameplay/gameplay_streams/scripts/survival/new_survival.h"


GameState Gameplay::startGameplay(sf::RenderWindow& mainWindow, const bool newGame, const std::string& saveFolder, PreSettings& preSettings)
{
	if (newGame)
	{
		PreSettings::validate(preSettings);
		world.createNew(preSettings);
		switch (preSettings.getGeneral().gameMode)
		{
		case GameMode::SANDBOX:
		case GameMode::SURVIVAL:
			createPlayerBase(world, preSettings);
			break;/*
		case GameMode::STORM:	not implemented
			break;
		case GameMode::PVP:		not implemented
			break;*/
		default:
			return GameState::MAIN_MENU;
		}
	}
	else
    {
		world.load(saveFolder);
    }
	
	player = world.getTeam("player");
	camera = Camera(world.getPreSettings().getTerrain().mapSize);
	minimap.initMapSize(world.getPreSettings().getTerrain().mapSize);
	buildingPanel.initPresettings(world.getPreSettings().getBuildings());

	std::thread simulation(&Gameplay::simulation, this);
	std::thread input(&Gameplay::input, this);
	std::thread scripts(&Gameplay::scripts, this);
	//std::thread network(&Gameplay::network, this);  not implemented
    graphics(mainWindow);

    simulation.join();
    input.join();
	scripts.join();
	//network.join(); not implemented
	return GameState::MAIN_MENU;
}


void Gameplay::relocateSubWindows(const sf::Vector2i windowSize)
{
	mainControlPanel.relocate(windowSize);
	resourcesPanel.relocate(windowSize);
	buildingPanel.relocate(windowSize);
	minimap.relocate(windowSize);
}

bool Gameplay::noSubWindowSelected() const
{
	return !mainControlPanel.containsCoursor() && !resourcesPanel.containsCoursor() &&
		!buildingPanel.containsCoursor() && !minimap.containsCoursor();
}
