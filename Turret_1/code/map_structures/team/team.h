#pragma once
#ifndef TEAM_H
#define TEAM_H

<<<<<<< Updated upstream
#include <vector>
#include <SFML/Graphics.hpp>

//#include "map_structures/entities/entities_list/entities_list.h"
//#include "map_structures/shells/shells_list/shells_list.h"
#include "map_structures/base_engine/tile_coord.h"

class Team
{
private:
	static std::vector<std::unique_ptr<Team>> teams;
	//EntitiesList entitiesList;
	//ShellsList shellsList;

public:
	Team();
	~Team() = default;

	void spawnShell(short type, const PixelCoord coord, float angleRad, float angleDeg);
	void spawnEntity(const int amount, const int type);


	void interact();

	void draw(sf::RenderWindow& window);

=======
#include <unordered_set>
#include <SFML/Graphics.hpp>

#include "map_structures/entities/entities_list/entities_list.h"
#include "map_structures/shells/shells_list/shells_list.h"
#include "map_structures/base_engine/tile_coord.h"


class Team
{
private:
	static inline std::unordered_set<std::shared_ptr<Team>> teams;
	EntitiesList entities;
	ShellsList shells;

	sf::String name;

	void interact();
	void draw(sf::RenderWindow& window);

public:
	Team(sf::String name);
	~Team() = default;

	static void addTeam(const sf::String& name);
	static void addTeam(const std::shared_ptr<Team> team);
	static void interactAll();
	static void drawAll(sf::RenderWindow& window);

	void spawnShell(short type, const PixelCoord coord, float angleRad, float angleDeg);
	void spawnEntity(const int amount, const int type);

>>>>>>> Stashed changes
};

#endif // TEAM_H
