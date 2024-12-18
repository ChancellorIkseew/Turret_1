#pragma once
#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <SFML/Graphics.hpp>
#include "game_interface/gameplay/gameplay_util/camera.h"

#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/terrain/terrain.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/particles/particles.h"
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
	Camera camera;

	MainControlPanel mainControlPanel;
	ResourcesPanel resourcesPanel;
	BuildingPanel buildingPanel;
	InventoryWindow inventoryWindow;

	std::shared_ptr<Team> player;
	std::shared_ptr<Team> enemy;

	void simulation();
	void input(sf::RenderWindow& mainWindow);
	void graphics(sf::RenderWindow& mainWindow);
	//void network();

	static inline Gameplay* instance = nullptr;

public:
	Gameplay();
	~Gameplay();

	int startGameplay(sf::RenderWindow& mainWindow, bool startNewGame, std::string saveFolderName);

	void relocateSubWindows(const sf::Vector2u windowSize);
	bool noSubWindowSelected();

	static Gameplay* getInstance();
	World& getWorld() { return world; }

};

#endif // GAMEPLAY_H
