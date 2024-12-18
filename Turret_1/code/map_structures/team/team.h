#pragma once
#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include <unordered_set>
#include <SFML/Graphics.hpp>

#include "map_structures/entities/entities_list/entities_list.h"
#include "map_structures/shells/shells_list/shells_list.h"
#include "map_structures/base_engine/base_engine.h"

#include "balance/balance.h"


class Team
{
private:
	int ID;
	sf::String name;

public:
	EntitiesList entities;
	ShellsList shells;
	Balance balance;

	Team(sf::String name);
	~Team() = default;

	void interact(const BuildingsMap& buildingsMap);
	void draw(sf::RenderWindow& window);

	void spawnShell(const uint16_t, const PixelCoord coord, float angleRad, float angleDeg);
	void spawnEntity(const uint8_t amount, const uint16_t);

	int getID();
	Balance& getBalance();

};

#endif // TEAM_H
