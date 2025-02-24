#pragma once
#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <optional>
#include <SFML/Graphics.hpp>
#include "game_interface/main_window/game_state.h"
#include "game_interface/gameplay/gameplay_util/camera.h"

#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/team/team.h"

#include "game_interface/gameplay/ui_elements/main_control_panel.h"
#include "game_interface/gameplay/ui_elements/resources_panel.h"
#include "game_interface/gameplay/ui_elements/building_panel.h"
#include "game_interface/gameplay/ui_elements/inventory_window.h"
#include "map_structures/world/world.h"


class Gameplay
{
private:
	bool isPaused = true;
	bool isGameplayActive = true;

	World world;
	Camera camera = Camera(TileCoord(0, 0));

	MainControlPanel mainControlPanel;
	ResourcesPanel resourcesPanel;
	BuildingPanel buildingPanel;
	InventoryWindow inventoryWindow;

	Team* player;

	void simulation();
	void input();
	void scripts();
	void graphics(sf::RenderWindow& mainWindow);
	//void network();

public:
	Gameplay() = default;
	~Gameplay() = default;

	GameState startGameplay(sf::RenderWindow& mainWindow, const bool newGame, std::string saveFolderName, std::optional<PreSettings> preSettings);

	void relocateSubWindows(const sf::Vector2u windowSize);
	bool noSubWindowSelected() const;

	World& getWorld() { return world; }

};

#endif // GAMEPLAY_H
