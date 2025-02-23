
#include <thread>

#include "gameplay.h"

#include "game_interface/main_window/main_window.h"

#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/team/team.h"
#include "map_structures/world/world.h"

#include "game_interface/gameplay/ui_elements/exit_confirmation.h"
#include "game_interface/gameplay/ui_elements/settings_window.h"


GameState Gameplay::startGameplay(sf::RenderWindow& mainWindow, const bool newGame, std::string saveFolderName, std::optional<PreSettings> preSettings)
{
	if (newGame)
	{
		world.createNew(preSettings.value());
		world.getBuildingsMap().placeBuilding(BuildingType::CORE_MK2, 0, TileCoord(48, 48), world.getTeam("player"));
		world.getTeam("player")->getBalance().giveStartRes(preSettings.value().getGeneral().startBalance);
	}
	else
    {
		world.load("save_1");
    }

	player = world.getTeam("player");
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
