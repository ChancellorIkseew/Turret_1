#pragma once
#ifndef WORLD_H
#define WORLD_H

#include "map_structures/team/team.h"
#include "map_structures/terrain/terrain.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/particles/particles.h"


class World
{
private:
	TerrainMap terrainMap;
	BuildingsMap buildingsMap;
	std::unordered_set<std::shared_ptr<Team>> teams;
	//ParticlesList particlesList; not implemented

public:
	World() = default;
	~World() = default;

	void save(const std::string& saveFolderName) const;
	void load(const std::string& saveFolderName);
	void createNew(const TileCoord mapSize);

	void simulate();
	void draw(sf::RenderWindow& window, const Camera& camera);

	TerrainMap& getTerrainMap() { return terrainMap; }
	BuildingsMap& getBuildingsMap() { return buildingsMap; }

	void addTeam(const sf::String& name)
	{
		teams.emplace(std::make_shared<Team>(name));
	}

	void addTeam(const std::shared_ptr<Team> team)
	{
		teams.emplace(team);
	}

};

#endif // WORLD_H
