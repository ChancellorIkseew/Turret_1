#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <unordered_map>

#include "map_structures/team/team.h"
#include "map_structures/terrain/terrain.h"
#include "map_structures/blueprints/blueprints_map.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/particles/particles_list/particles_list.h"
#include "map_structures/pre-settings/pre-settings.h"
#include "game_interface/gameplay/gameplay_util/t1_time.h"

class WaveConstructor;

class World
{
private:
	PreSettings preSettings;
	TerrainMap terrainMap;
	BlueprintsMap blueprintsMap;
	BuildingsMap buildingsMap;
	std::unordered_map<int, std::unique_ptr<Team>> teams;
	ParticlesList particles;
	t1::Time time;
	int nextTeamID = 0;

public:
	World();
	~World() = default;

	void save(const std::string& folder) const;
	void load(const std::string& folder);
	void createNew(const PreSettings& preSettings);

	void simulate();
	void draw(sf::RenderWindow& window, const Camera& camera);

	BlueprintsMap& getBlueprintsMap() { return blueprintsMap; }
	BuildingsMap& getBuildingsMap() { return buildingsMap; } // non_const
	ParticlesList& getParticles() { return particles; }
	Team* getTeam(const int ID) { return teams.at(ID).get(); }
	std::unordered_map<int, std::unique_ptr<Team>>& getTeams() { return teams; }
	
	const PreSettings& getPreSettings() const { return preSettings; };
	const TerrainMap& getTerrainMap() const { return terrainMap; }
	const BlueprintsMap& getBlueprintsMap() const { return blueprintsMap; }
	const BuildingsMap& getBuildingsMap() const { return buildingsMap; }
	const t1::Time& getTime() const { return time; }
	const std::unordered_map<int, std::unique_ptr<Team>>& getTeams() const { return teams; }

	void addTeam(const std::string& name, const sf::Color& color);
	Team* getTeam(const std::string& name);
	friend WaveConstructor;
};

#endif // WORLD_H
