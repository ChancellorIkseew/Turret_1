#pragma once
#ifndef TEAM_H
#define TEAM_H

#include <SFML/Graphics.hpp>
#include <cereal/archives/binary.hpp>

#include "map_structures/entities/entities_list/entities_list.h"
#include "map_structures/shells/shells_list/shells_list.h"
#include "map_structures/base_engine/base_engine.h"

#include "balance/balance.h"

class Camera;

class Team
{
private:
	int ID;
	std::string name;

public:
	EntitiesList entities;
	ShellsList shells;
	Balance balance;

	Team(std::string name);
	Team() = default;
	~Team() = default;

	void save(cereal::BinaryOutputArchive& archive) const;
	void load(cereal::BinaryInputArchive& archive);

	void interact(const BuildingsMap& buildingsMap);
	void draw(sf::RenderWindow& window, const Camera& camera);

	void spawnShell(const uint16_t, const PixelCoord coord, float angleRad, float angleDeg);
	void spawnEntity(const uint8_t amount, const uint16_t, const BuildingsMap& buildingsMap);

	int getID();
	Balance& getBalance();

};

#endif // TEAM_H
