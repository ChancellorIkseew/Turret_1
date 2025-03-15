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
	int ID = 0;
	std::string name;
	sf::Color color;

	EntitiesList entities;
	ShellsList shells;
	Balance balance;

public:
	Team(const std::string& name, const sf::Color& color, const int ID);
	Team() = default;
	~Team() = default;

	void save(cereal::BinaryOutputArchive& archive) const;
	void load(cereal::BinaryInputArchive& archive);

	void interact(const BuildingsMap& buildingsMap);
	void draw(sf::RenderWindow& window, const Camera& camera);

	void spawnShell(const ShellType type, const PixelCoord coord, const float angleRad);
	void spawnEntity(const MobType type, const PixelCoord coord, const Control control);

	Balance& getBalance() { return balance; }
	EntitiesList& getEneities() { return entities; }
	ShellsList& getShells() { return shells; }

	const int getID() const { return ID; }
	const std::string& getName() const { return name; }
	const sf::Color& getColor() const { return color; }
	const Balance& getBalance() const { return balance; }
	const EntitiesList& getEneities() const { return entities; }
	const ShellsList& getShells() const { return shells; }

	void setColor(const sf::Color& color) {
		this->color = color;
	}

};

#endif // TEAM_H
