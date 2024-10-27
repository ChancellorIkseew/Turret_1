#pragma once
#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <SFML/Graphics.hpp>

#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/terrain/terrain.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/particles/particles.h"
#include "map_structures/team/team.h"

#include "game_interface/gameplay/gameplay_util/cheet_commands.h"
#include "game_interface/gameplay/ui_elements/main_control_panel.h"
#include "game_interface/gameplay/ui_elements/resources_panel.h"
#include "game_interface/gameplay/ui_elements/building_panel.h"


class Gameplay
{
private:
	bool isMovingCamera = false;
	sf::Vector2f lastMousePosition;

	sf::Vector2i mouseCoord;
	sf::Vector2f mouseMapCoord;

	bool isPaused = true;
	bool isGameplayActive = true;

	MainControlPanel mainControlPanel;
	ResourcesPanel resourcesPanel;
	BuildingPanel buildingPanel;

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
	bool noSubWindowSelected(const sf::Vector2i mouseCoord);

	static Gameplay* getInstance();

};

#endif // GAMEPLAY_H
